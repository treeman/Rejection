#include "World.hpp"

#include <boost/foreach.hpp>
#include "Tree/Log.hpp"
#include "GrassTiles.hpp"
#include "Tweaks.hpp"

bool can_kill( boost::shared_ptr<Girl> girl )
{
	return girl->CanKill();
}

World::World( boost::shared_ptr<SpriteLoader> _spr_loader ) : grid( 0, 32, 25, 30, 32, 18 ),
	spr_loader( _spr_loader )
{
	InitTiles();
	
	dude.reset( new Dude( spr_loader ) );
	girl_controller.reset( new GirlController() );
	
	time_machine.reset( new TimeMachine( spr_loader ) );
	dude_working = spr_loader->Get( "hm" );
	
	working.Load( "sound/clock.wav" );
	
	InitDebug();
	
	NewGame();
}

boost::shared_ptr<Dude> World::GetDude()
{
	return dude;
}

void World::AddListener( WorldListener *l )
{
	listeners.push_back( l );
}

void World::NewGame()
{
	//reset tiles growth
	for( size_t x = 0; x < grid.GetColumns(); ++x ) {
		for( size_t y = 0; y < grid.GetRows(); ++y ) {
			tiles[x][y]->Reset();
			tiles[x][y]->Detach();
		}
	}
	
	traps.clear();
	girls.clear();
	
	dude->SetPos( grid.ConvertToScreen( GridPos( 5, 0 ) ) );
	dude->MoveStop();
	
	time_machine->SetCompletePerc( 0 );
	time_machine->SetPos( grid.ConvertToScreen( GridPos( 14, 0 ) ) );
	tiles[14][0]->Attach( time_machine );
	
	for( int n = 0; n < (int)TWEAKS->GetFloat( "starting_girls" ); ++n ) {
		SpawnGirl();
	}
	
	SetMoney( (int)TWEAKS->GetFloat( "money" ) );
	SetLife( (int)TWEAKS->GetFloat( "life" ) );
}

bool World::GameComplete()
{
	return time_machine->GetCompletePerc() > 0.99;
}
bool World::GameOver()
{
	return life == 0;
}

bool World::IsDudeFacingBuildableTile()
{
	const GridPos dude_pos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
	
	GridPos action_pos;
		
	if( dude->FacesLeft() ) { action_pos = GridPos( dude_pos.x - 1, dude_pos.y ); }
	else if( dude->FacesRight() ) { action_pos = GridPos( dude_pos.x + 1, dude_pos.y ); }
	else if( dude->FacesUp() ) { action_pos = GridPos( dude_pos.x, dude_pos.y - 1 ); }
	else if( dude->FacesDown() ) { action_pos = GridPos( dude_pos.x, dude_pos.y + 1 ); }
	
	return action_pos != grid.ConvertToGrid( time_machine->GetPos() ) && IsValid( action_pos );
}

bool World::BuyTrap( boost::shared_ptr<Trap> trap )
{
	const GridPos dude_pos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
	
	GridPos action_pos;
		
	if( dude->FacesLeft() ) { 
		action_pos = GridPos( dude_pos.x - 1, dude_pos.y );
		trap->FaceRight();
	}
	else if( dude->FacesRight() ) { 
		action_pos = GridPos( dude_pos.x + 1, dude_pos.y ); 
		trap->FaceLeft();
	}
	else if( dude->FacesUp() ) { 
		action_pos = GridPos( dude_pos.x, dude_pos.y - 1 ); 
		trap->FaceDown();
	}
	else if( dude->FacesDown() ) { 
		action_pos = GridPos( dude_pos.x, dude_pos.y + 1 ); 
		trap->FaceUp();
	}
	
	//check our funds
	if( money >= trap->GetInfo().cost && IsValid( action_pos ) && tiles[action_pos.x][action_pos.y]->Attach( trap ) ) {
		//withdraw funds
		traps.push_back( trap );
		SetMoney( money - trap->GetInfo().cost );
	}
	else {
		return false;
	}
}

bool World::CanSellTrap()
{
	const GridPos dude_pos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
	
	GridPos action_pos;
		
	if( dude->FacesLeft() ) { action_pos = GridPos( dude_pos.x - 1, dude_pos.y ); }
	else if( dude->FacesRight() ) { action_pos = GridPos( dude_pos.x + 1, dude_pos.y ); }
	else if( dude->FacesUp() ) { action_pos = GridPos( dude_pos.x, dude_pos.y - 1 ); }
	else if( dude->FacesDown() ) { action_pos = GridPos( dude_pos.x, dude_pos.y + 1 ); }
	
	for( Traps::iterator it = traps.begin(); it != traps.end(); ++it ) {
		if( grid.ConvertToGrid( (*it)->GetPos() ) == action_pos ) {
			SetMoney( money + (*it)->GetInfo().cost );
			
			tiles[action_pos.x][action_pos.y]->Detach();
			traps.erase( it );
			return true;
		}
	}
	return false;
}

//don't ask
struct BlowPos {
	GridPos pos;
	Vec2D dir;
	float power;
};

void World::Update( float dt )
{
	girl_controller->Update( dt );
	
	typedef std::vector<GridPos> Positions;
	Positions activate_trap_on;
	
	typedef std::vector<BlowPos> BlowPositions;
	BlowPositions blow_positions;
	
	//update the traps
	BOOST_FOREACH( boost::shared_ptr<Trap> trap, traps ) {
		const GridPos grid_pos = grid.ConvertToGrid( trap->GetPos() );
		
		//add positions to activate
		const int activation_radius = trap->GetActivationRadius();
		if( activation_radius > 0 ) {
			for( int x = grid_pos.x - activation_radius; x < grid_pos.x + activation_radius; ++x ) {
				for( int y = grid_pos.y - activation_radius; y < grid_pos.y + activation_radius; ++y ) {
					if( grid_pos.x == x && grid_pos.y == y ) { continue; }
					else { activate_trap_on.push_back( GridPos( x, y ) ); }
				}
			}
		}
		
		//set blowing on tiles
		const int blow_length = trap->GetBlowLength();
		if( blow_length > 0 ) {
			const Vec2D blow_dir = trap->GetBlowDir();
			const Vec2D face_dir = trap->GetFaceDir();
			
//			L_ << "blow_dir: " << blow_dir.x << "," << blow_dir.y;
//			L_ << "face_dir: " << face_dir.x << "," << face_dir.y;
//			
//			L_ << "my_pos: " << grid_pos.x << "," << grid_pos.y;
			
			if( face_dir == Vec2D::left ) {
//				L_ << "left blow";
				
				int right = grid_pos.x - 1;
				int left = right - blow_length;
				
//				L_ << "l: " << left << " r: " << right;
				
				int n = 0;
				for( int x = right; x > left; --x, ++n ) {
					BlowPos p;
					p.dir = blow_dir;
					p.pos = GridPos( x, grid_pos.y );
					p.power = 1.0 / n;
					if( IsWalkable( p.pos ) ) {
//						L_ << "blowing: " << p.pos.x << "," << p.pos.y;
						blow_positions.push_back( p );
					}
					else { break; }
				}
			}
			else if( face_dir == Vec2D::right ) {
//				L_ << "right blow";
				
				int left = grid_pos.x + 1;
				int right = left + blow_length;
				
//				L_ << "l: " << left << " r: " << right;
				
				int n = 0;
				for( int x = left; x < right; ++x, ++n ) {
					BlowPos p;
					p.dir = blow_dir;
					p.pos = GridPos( x, grid_pos.y );
					p.power = 1.0 / n;
					if( IsWalkable( p.pos ) ) {
//						L_ << "blowing: " << p.pos.x << "," << p.pos.y;
						blow_positions.push_back( p );
					}
					else { break; }
				}
			}
			else if( face_dir == Vec2D::up ) {
//				L_ << "up blow";
				
				int down = grid_pos.y - 1;
				int up = down - blow_length;
				
//				L_ << "u: " << up << " d: " << down;
				
				int n = 0;
				for( int y = down; y > up; --y, ++n ) {
					BlowPos p;
					p.dir = blow_dir;
					p.pos = GridPos( grid_pos.x, y );
					p.power = 1.0 / n;
					if( IsWalkable( p.pos ) ) {
//						L_ << "blowing: " << p.pos.x << "," << p.pos.y;
						blow_positions.push_back( p );
					}
					else { break; }
				}
			}
			else if( face_dir == Vec2D::down ) {
//				L_ << "down blow";
				
				int up = grid_pos.y + 1;
				int down = up + blow_length;
				
//				L_ << "u: " << up << " d: " << down;
				
				int n = 0;
				for( int y = up; y < down; ++y, ++n ) {
					BlowPos p;
					p.dir = blow_dir;
					p.pos = GridPos( grid_pos.x, y );
					p.power = 1.0 / n;
					if( IsWalkable( p.pos ) ) {
//						L_ << "blowing: " << p.pos.x << "," << p.pos.y;
						blow_positions.push_back( p );
					}
					else { break; }
				}
			}
		}
	}
	
//	if( !activate_trap_on.empty() ) {
//		L_ << "here they are:";
//		BOOST_FOREACH( GridPos p, activate_trap_on ) {
//			L_ << p.x << "," << p.y;
//		}
//	}

//	if( !blow_positions.empty() ) {
//		L_ << "blow positions: " ;
//		BOOST_FOREACH( BlowPos p, blow_positions ) {
//			L_ << p.pos.x << "," << p.pos.y;
//		}
//	}
	
	//update the tiles
	for( size_t x = 0; x < tiles.size(); ++x ) {
		for( size_t y = 0; y < tiles[x].size(); ++y ) {
			const TilePtr tile = tiles[x][y];
			const GridPos grid_pos = grid.ConvertToGrid( tile->GetPos() );
			
			const Vec2D flow_dir = tile->GetFlowDirection();
			const float flow_power = tile->GetFlowPower();
			
			if( dude->Bounds().Intersects( tile->Bounds() ) )
			{
				tile->WalkOver();
				
				if( flow_dir != Vec2D::zero ) {
					if( flow_dir == Vec2D::left ) dude->PushLeft( flow_power );
					else if( flow_dir == Vec2D::right ) dude->PushRight( flow_power );
					else if( flow_dir == Vec2D::up ) dude->PushUp( flow_power );
					else if( flow_dir == Vec2D::down ) dude->PushDown( flow_power );
					AddTrapMoney();
				}
			}
			else {
				BOOST_FOREACH( boost::shared_ptr<Girl> girl, girls ) {
					if( girl->Bounds().Intersects( tile->Bounds() ) )
					{
						tile->WalkOver();
						if( flow_dir != Vec2D::zero ) {
							if( flow_dir == Vec2D::left ) girl->PushLeft( flow_power );
							else if( flow_dir == Vec2D::right ) girl->PushRight( flow_power );
							else if( flow_dir == Vec2D::up ) girl->PushUp( flow_power );
							else if( flow_dir == Vec2D::down ) girl->PushDown( flow_power );
							AddTrapMoney();
						}
					}
				}
			}
			
			//update blowing
			if( tile->IsWalkable() ) {
				BlowPositions::iterator it;
				for( it = blow_positions.begin(); it != blow_positions.end(); ++it ) {
					if( it->pos == grid_pos ) break;
				}
					
				if( it != blow_positions.end() ) {
					tile->SetFlowDirection( it->dir, it->power );
					blow_positions.erase( it );
				}
				else {
					tile->ClearFlow();
				}
			}
			else {
				tile->ClearFlow();
			}
			
			//activate attachments
			if( tile->Attachment() ) {
//				if( !activate_trap_on.empty() ) {
//					GridPos p = grid.ConvertToGrid( tile->Attachment()->GetPos() );
//					L_ << "here's something: " << p.x << "," << p.y;
//				}
				Positions::iterator it = std::find( activate_trap_on.begin(), 
					activate_trap_on.end(), grid_pos );
													
				if( it != activate_trap_on.end() ) {
//					L_ << "oh, something found!!!";
					tile->Attachment()->Activate();
					activate_trap_on.erase( it );
				}
			}
			
			tile->Update( dt );
		}
	}
	
	BOOST_FOREACH( boost::shared_ptr<Girl> girl, girls ) {
		UpdatePerson( girl, dt );
	}
	girls.erase( std::remove_if( girls.begin(), girls.end(), can_kill ), girls.end() );
	
	UpdateDude( dude, dt );
	
	time_machine->Update( dt );
}
void World::Render()
{
	float mx, my;
	hge->Input_GetMousePos( &mx, &my );
	
	for( size_t x = 0; x < tiles.size(); ++x ) {
		for( size_t y = 0; y < tiles[x].size(); ++y ) {
			const Tree::Rect r = tiles[x][y]->Bounds();
			
			tiles[x][y]->Render();
			if( show_bounds->Val() ) {
				hgeh::render_rect( hge, r.x1, r.y1, r.x2, r.y2, 0xff666666 );
			}
		}
	}
	
	time_machine->Render();
	if( WorkingOnTimeMachine() ) {
		Vec2D pos( time_machine->GetPos() );
		pos.x += 6;
		dude_working->spr->Render( pos.x, pos.y );
	}
	
	BOOST_FOREACH( boost::shared_ptr<Girl> girl, girls ) {
		RenderPerson( girl );
	}
	RenderPerson( dude );
	
	if( show_bounds->Val() ) {
		const Tree::Rect r = dude->Bounds();
		hgeh::render_rect( hge, r.x1, r.y1, r.x2, r.y2, 0xffdc6218 );
	}
	
	if( show_mouse_grid->Val() ) {
		fnt->SetColor( 0xffffffff );
		
		GridPos grid_pos = grid.ConvertToGrid( Vec2D( mx, my ) );
		Vec2D mpos = grid.ConvertToScreen( grid_pos );
		fnt->printf( 50, 15, HGETEXT_LEFT, "%i,%i => %.0f,%.0f", grid_pos.x, grid_pos.y,
			mpos.x, mpos.y );
	}
	
	if( debug_dude->Val() ) {
		GridPos grid_pos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
		Vec2D gpos = grid.ConvertToScreen( grid_pos );
		fnt->printf( 750, 5, HGETEXT_RIGHT, "dude_grid:%i,%i=>%.0f,%.0f", grid_pos.x, grid_pos.y,
			gpos.x, gpos.y );
	}
	
	if( debug_complete->Val() ) {
		float complete = time_machine->GetCompletePerc();
		fnt->printf( 600, 10, HGETEXT_LEFT, "complete: %.2f", complete );
	}
	
	if( debug_traps->Val() ) {
		const int x = 795;
		const int y1 = 30;
		const int h = 10;
		
		int n = 0;
		BOOST_FOREACH( boost::shared_ptr<Trap> trap, traps ) {
			bool is_active = trap->IsActive();
			Vec2D face_dir = trap->GetFaceDir();
			Vec2D blow_dir = trap->GetBlowDir();
			int activation_radius = trap->GetActivationRadius();
			int blow_length = trap->GetBlowLength();
			
			Vec2D pos = trap->GetPos();
			
			fnt->printf( x, y1 + h * n, HGETEXT_RIGHT, 
				"is_active: %i face_dir: %.0f,%.0f blow_dir: %.0f,%.0f r: %i blow_length: %i",
				is_active, face_dir.x, face_dir.y, blow_dir.x, blow_dir.y, blow_length );
			
			++n;
		}
	}
}

void World::UpdateDude( boost::shared_ptr<Dude> dude, float dt )
{
	UpdatePerson( dude, dt );

	if( WorkingOnTimeMachine() ) {
		const int cost = (int)TWEAKS->GetFloat( "time_machine_construction_cost" ) * dt;
		if( money >= cost ) {
			time_machine->SetCompletePerc( TWEAKS->GetFloat( "time_machine_construction_rate" ) * dt +
				time_machine->GetCompletePerc() );
			SetMoney( money - cost );
			
			if( !hge->Channel_IsPlaying( working_channel ) ) {
				working_channel = hge->Effect_PlayEx( working, 50 );
			}
		}
	}
	else {
		hge->Channel_Stop( working_channel );
	}
	
	BOOST_FOREACH( boost::shared_ptr<Girl> girl, girls ) {
		if( dude->Bounds().Intersects( girl->Bounds() ) ) {
			girl->Kill();
			SetLife( life - 1 );
		}
	}
}

void World::UpdatePerson( boost::shared_ptr<Person> o, float dt )
{
	o->Update( dt );
	
	//a grid pos will be a valid array index
	const GridPos grid_pos = grid.ConvertToGrid( o->Bounds().GetCenter() );
	
	//check stop targets
	if( o->WantsStop() ) 
	{
		if( o->WantsLeft() ) 
		{
			//if we can walk to the left and if we're intersecting with it
			if( IsWalkable( grid_pos.x - 1, grid_pos.y ) &&
				tiles[grid_pos.x - 1][grid_pos.y]->Bounds().Intersects( o->Bounds() ) ) 
			{
				o->StopAt( grid.ConvertToScreen( GridPos( grid_pos.x - 1, grid_pos.y ) ) );
			}
			//else stop it immediatly
			else {
				o->StopAt( grid.ConvertToScreen( grid_pos ) );
			}
		}
		else if( o->WantsRight() ) 
		{
			//same but to the right
			if( IsWalkable( grid_pos.x + 1, grid_pos.y ) &&
				tiles[grid_pos.x + 1][grid_pos.y]->Bounds().Intersects( o->Bounds() ) ) 
			{
				o->StopAt( grid.ConvertToScreen( GridPos( grid_pos.x + 1, grid_pos.y ) ) );
			}
			else {
				o->StopAt( grid.ConvertToScreen( grid_pos ) );
			}
		}
		//up and down compare to left and right
		else if( o->WantsUp() ) 
		{
			if( IsWalkable( grid_pos.x, grid_pos.y - 1 ) &&
				tiles[grid_pos.x][grid_pos.y - 1]->Bounds().Intersects( o->Bounds() ) ) 
			{
				o->StopAt( grid.ConvertToScreen( GridPos( grid_pos.x, grid_pos.y - 1 ) ) );
			}
			else {
				o->StopAt( grid.ConvertToScreen( grid_pos ) );
			}
		}
		else if( o->WantsDown() ) 
		{
			if( IsWalkable( grid_pos.x, grid_pos.y + 1 ) &&
				tiles[grid_pos.x][grid_pos.y + 1]->Bounds().Intersects( o->Bounds() ) ) 
			{
				o->StopAt( grid.ConvertToScreen( GridPos( grid_pos.x, grid_pos.y + 1 ) ) );
			}
			else {
				o->StopAt( grid.ConvertToScreen( grid_pos ) );
			}
		}
	}
	
	CheckCollisions( o );
	
	Person::Vision vision = o->GetVision();
	const GridPos self_pos( vision.size() / 2, vision[0].size() / 2 );
	const GridPos dude_pos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
	
	for( int y = 0; y < vision.size(); ++y ) {
		for( int x = 0; x < vision[y].size(); ++x ) {
			
			if( self_pos.x == x && self_pos.y == y ) {
				vision[x][y] = VISION_SELF;
				continue;
			}
			
			const GridPos rel_grid_pos( 
				grid_pos.x - self_pos.x + x,
				grid_pos.y - self_pos.y + y
			);
			
			if( dude_pos == rel_grid_pos ) { 
				vision[x][y] = VISION_DUDE; 
			}
			else if( IsSeeThrough( rel_grid_pos ) ) {
				vision[x][y] = VISION_FREE; 
			}
			else if( !IsValid( rel_grid_pos ) ) { 
				vision[x][y] = VISION_INVALID; 
			}
			else {
				vision[x][y] = VISION_OBSUCRED;
			}
		}
	}
	
	o->SetVision( vision );
}

void World::RenderPerson( boost::shared_ptr<Person> o )
{
	o->Render();
}

void World::CheckCollisions( boost::shared_ptr<MovingObject> o )
{
	const GridPos grid_pos = grid.ConvertToGrid( o->Bounds().GetCenter() );
	
	if( Collision( o->Bounds(), grid_pos.x - 1, grid_pos.y ) ) {
			o->SetPos( grid.ConvertToScreen( grid_pos ) );
			o->MoveStop();
	}
	else if( Collision( o->Bounds(), grid_pos.x + 1, grid_pos.y ) ) {
			o->SetPos( grid.ConvertToScreen( grid_pos ) );
			o->MoveStop();
	}
	else if( Collision( o->Bounds(), grid_pos.x, grid_pos.y - 1 ) ) {
			o->SetPos( grid.ConvertToScreen( grid_pos ) );
			o->MoveStop();
	}
	else if( Collision( o->Bounds(), grid_pos.x, grid_pos.y + 1 ) ) {
			o->SetPos( grid.ConvertToScreen( grid_pos ) );
			o->MoveStop();
	}
}

bool World::Collision( Tree::Rect bounds, int x, int y )
{
	if( !IsValid( x, y ) ) {
		float x1, y1, x2, y2;
		grid.GetBounds( x1, y1, x2, y2 );
		
		return bounds.x1 < x1 || bounds.x2 > x2 ||
			bounds.y1 < y1 || bounds.y2 > y2;
	}
	else {
		return !IsWalkable( x, y ) && bounds.Intersects( tiles[x][y]->Bounds() );
	}
}

void World::SpawnGirl()
{
	boost::shared_ptr<Girl> girl( new Girl( spr_loader ) );
	GridPos pos( math::irandom( 0, grid.GetColumns() ),
			     math::irandom( 0, grid.GetRows() ) );
	girl->SetPos( grid.ConvertToScreen( pos ) );
	girl_controller->Attach( girl );
	
	girls.push_back( girl );
}
void World::KillGirl( boost::shared_ptr<Girl> girl )
{
	girl_controller->Detach( girl );
	std::remove( girls.begin(), girls.end(), girl );
}

void World::InitTiles()
{
	int n = 0;
	for( size_t x = 0; x < grid.GetColumns(); ++x, ++n ) {
		Tiles column;
		for( size_t y = 0; y < grid.GetRows(); ++y, ++n ) {
			TilePtr tile;
			if( n % 2 == 0 ) {
				tile.reset( new LightGrassTile( grid.ConvertToScreen( GridPos( x, y ) ), spr_loader ) );
			}
			else {
				tile.reset( new DarkGrassTile( grid.ConvertToScreen( GridPos( x, y ) ), spr_loader ) );
			}
			column.push_back( tile );
		}
		tiles.push_back( column );
	}
	
	//spell G33k on the grass xD
	Geekify();
}
void World::Geekify()
{
	//G
	for( int x = 2; x < 6; ++x ) Geekify(x,5);
	for( int y = 6; y < 11; ++y ) Geekify(2,y);
	for( int x = 3; x < 7; ++x ) Geekify(x,10);
	Geekify(6,9); Geekify(6,8); Geekify(5,8);
	
	//first 3
	for( int x = 8; x < 11; ++x ) Geekify(x,6);
	for( int x = 8; x < 11; ++x ) Geekify(x,10);
	for( int x = 9; x < 11; ++x ) Geekify(x,8);
	for( int y = 7; y < 10; ++y ) Geekify(11,y);
	
	//2nd 3
	for( int x = 13; x < 16; ++x ) Geekify(x,6);
	for( int x = 13; x < 16; ++x ) Geekify(x,10);
	for( int x = 14; x < 16; ++x ) Geekify(x,8);
	for( int y = 7; y < 10; ++y ) Geekify(16,y);
	
	//K
	for( int y = 6; y < 11; ++y ) Geekify(18,y);
	Geekify(21,6);
	Geekify(20,7);
	Geekify(19,8);
	Geekify(20,9);
	Geekify(21,10);
}
void World::Geekify( int x, int y )
{
	GrassTile *tile = dynamic_cast<GrassTile*>( tiles[x][y].get() );
	if( tile->IsDark() ) {
		tiles[x][y].reset( new GeekDarkGrassTile( grid.ConvertToScreen( GridPos( x, y ) ), spr_loader ) );
	}
	else {
		tiles[x][y].reset( new GeekLightGrassTile( grid.ConvertToScreen( GridPos( x, y ) ), spr_loader ) );
	}
}
bool World::IsWalkable( int x, int y )
{
	if( !IsValid( x, y ) ) return false;
	else return tiles[x][y]->IsWalkable();
}
bool World::IsSeeThrough( int x, int y )
{
	if( !IsValid( x, y ) ) return false;
	else {
		return tiles[x][y]->IsSeeThrough();
	}
}
bool World::IsValid( int x, int y )
{
	return x >= 0 && x < grid.GetColumns() && y >= 0 && y < grid.GetRows();
}

bool World::WorkingOnTimeMachine()
{
	if( dude->WantsAction() ) {
		const GridPos grid_pos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
		GridPos action_pos;
		
		if( dude->FacesLeft() ) { action_pos = GridPos( grid_pos.x - 1, grid_pos.y ); }
		else if( dude->FacesRight() ) { action_pos = GridPos( grid_pos.x + 1, grid_pos.y ); }
		else if( dude->FacesUp() ) { action_pos = GridPos( grid_pos.x, grid_pos.y - 1 ); }
		else if( dude->FacesDown() ) { action_pos = GridPos( grid_pos.x, grid_pos.y + 1 ); }
		
		return action_pos == grid.ConvertToGrid( time_machine->GetPos() );
	}
	else { return false; }
}

void World::SetMoney( int m )
{
	money = m;
	BOOST_FOREACH( WorldListener *l, listeners ) {
		l->SetMoney( money );
	}
}
void World::AddTrapMoney()
{
	SetMoney( money + (int)TWEAKS->GetFloat( "trap_money" ) );
}

void World::SetLife( int l )
{
	life = l;
	BOOST_FOREACH( WorldListener *l, listeners ) {
		l->SetLife( life );
	}
}

void World::InitDebug()
{
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	show_mouse_grid.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "mouse_grid_pos_show", boost::weak_ptr<Tree::BaseDator>( show_mouse_grid ) );
	
	show_bounds.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "bounds_show", boost::weak_ptr<Tree::BaseDator>( show_bounds ) );
	
	debug_dude.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "dude_debug", boost::weak_ptr<Tree::BaseDator>( debug_dude ) );
	
	debug_traps.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "traps_debug", boost::weak_ptr<Tree::BaseDator>( debug_traps ) );
	
	debug_complete.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "completion_debug", boost::weak_ptr<Tree::BaseDator>( debug_complete ) );
}
