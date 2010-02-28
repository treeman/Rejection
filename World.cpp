#include "World.hpp"

#include <boost/foreach.hpp>
#include "Tree/Log.hpp"
#include "GrassTiles.hpp"
#include "Tweaks.hpp"

World::World( boost::shared_ptr<SpriteLoader> _spr_loader ) : grid( 0, 32, 25, 30, 32, 18 ),
	spr_loader( _spr_loader )
{
	InitTiles();
	
	dude.reset( new Dude( spr_loader ) );
	girl_controller.reset( new GirlController() );
	
//	for( int n = 0; n < 5; ++n ) {
//		SpawnGirl();
//	}
	
	time_machine.reset( new TimeMachine( spr_loader ) );
	time_machine->SetPos( grid.ConvertToScreen( GridPos( 14, 0 ) ) );
	
	tiles[14][0]->Attach( time_machine );
	
	dude_working = spr_loader->Get( "hm" );
	
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
	dude->SetPos( grid.ConvertToScreen( GridPos( 5, 0 ) ) );
	time_machine->SetCompletePerc( 0 );
	
	//reset tiles growth
	for( size_t x = 0; x < grid.GetColumns(); ++x ) {
		for( size_t y = 0; y < grid.GetRows(); ++y ) {
			tiles[x][y]->Reset();
		}
	}
}

bool World::GameComplete()
{
	return time_machine->GetCompletePerc() > 0.99;
}
bool World::GameOver()
{
	return false;
}

void World::Update( float dt )
{
	girl_controller->Update( dt );
	
	BOOST_FOREACH( boost::shared_ptr<Girl> girl, girls ) {
		UpdatePerson( girl, dt );
	}
	UpdateDude( dude, dt );
	
	for( size_t x = 0; x < tiles.size(); ++x ) {
		for( size_t y = 0; y < tiles[x].size(); ++y ) {
			const TilePtr tile = tiles[x][y];
			
			if( dude->Bounds().Intersects( tile->Bounds() ) )
			{
				tile->WalkOver();
			}
			else {
				BOOST_FOREACH( boost::shared_ptr<Girl> girl, girls ) {
					if( girl->Bounds().Intersects( tile->Bounds() ) )
					{
						tile->WalkOver();
					}
				}
			}
			tile->Update( dt );
		}
	}
	
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
	
	float complete = time_machine->GetCompletePerc();
	fnt->printf( 700, 10, HGETEXT_LEFT, "complete: %.2f", complete );
}

void World::UpdateDude( boost::shared_ptr<Dude> dude, float dt )
{
	UpdatePerson( dude, dt );

	if( WorkingOnTimeMachine() ) {
		time_machine->SetCompletePerc( TWEAKS->GetFloat( "time_machine_contruction_rate" ) * dt +
			time_machine->GetCompletePerc() );
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

void World::InitDebug()
{
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	show_mouse_grid.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "mouse_grid_pos_show", boost::weak_ptr<Tree::BaseDator>( show_mouse_grid ) );
	
	show_bounds.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "bounds_show", boost::weak_ptr<Tree::BaseDator>( show_bounds ) );
	
	debug_dude.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "dude_debug", boost::weak_ptr<Tree::BaseDator>( debug_dude ) );
}
