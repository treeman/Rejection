#include "World.hpp"

#include <boost/foreach.hpp>
#include "Tree/Log.hpp"
#include "GrassTiles.hpp"

World::World( boost::shared_ptr<SpriteLoader> _spr_loader ) : grid( 32, 32, 23, 32, 32, 17 ),
	spr_loader( _spr_loader )
{
	InitTiles( spr_loader );
	
	dude.reset( new Dude( spr_loader ) );
	dude->SetPos( grid.ConvertToScreen( GridPos( 5, 0 ) ) );
	
	girl_controller.reset( new GirlController() );
	
	SpawnGirl();
	
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	show_mouse_grid.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "mouse_grid_pos_show", boost::weak_ptr<Tree::BaseDator>( show_mouse_grid ) );
	
	show_bounds.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "bounds_show", boost::weak_ptr<Tree::BaseDator>( show_bounds ) );
	
	debug_dude.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "dude_debug", boost::weak_ptr<Tree::BaseDator>( debug_dude ) );
}

boost::shared_ptr<Dude> World::GetDude()
{
	return dude;
}

void World::Update( float dt )
{
	girl_controller->Update( dt );
	
	BOOST_FOREACH( boost::shared_ptr<Girl> girl, girls ) {
		UpdatePerson( girl, dt );
	}
	UpdatePerson( dude, dt );
	
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
	
	CheckWorldBounds( o );
	
	Person::Vision vision = o->GetVision();
	const GridPos self_pos( vision.size() / 2, vision[0].size() / 2 );
	const GridPos dude_pos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
	
//	L_ << "person updating stuff:";
//	L_ << "self_pos: " << self_pos.x << "," << self_pos.y;
//	L_ << "dude_pos: " << dude_pos.x << "," << dude_pos.y;
//	L_ << "grid_pos: " << grid_pos.x << "," << grid_pos.y;
	
	for( int y = 0; y < vision.size(); ++y ) {
		for( int x = 0; x < vision[y].size(); ++x ) {
			
			if( self_pos.x == x && self_pos.y == y ) {
				vision[x][y] = VISION_SELF;
//				L_ << "self found! :D";
				continue;
			}
			
			const GridPos rel_grid_pos( 
				grid_pos.x - self_pos.x + x,
				grid_pos.y - self_pos.y + y
			);
			
//			L_ << "rel_grid_pos: " << rel_grid_pos.x << "," << rel_grid_pos.y;
			
			if( dude_pos == rel_grid_pos ) { 
				vision[x][y] = VISION_DUDE; 
			}
			else if( IsSeeThrough( rel_grid_pos ) ) {
//				L_ << "oh it's free alright!";
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

void World::CheckWorldBounds( boost::shared_ptr<MovingObject> o )
{
	float x1, y1, x2, y2;
	grid.GetBounds( x1, y1, x2, y2 );
	
	const Tree::Rect b(
		o->GetPos().x,
		o->GetPos().y,
		32, 32 );
	
	if( b.x1 < x1 ) o->SetXPos( x1 );
	if( b.x2 > x2 ) o->SetXPos( x2 - b.Width() );
	
	if( b.y1 < y1 ) o->SetYPos( y1 );
	if( b.y2 > y2 ) o->SetYPos( y2 - b.Height() );
}

void World::SpawnGirl()
{
	boost::shared_ptr<Girl> girl( new Girl( spr_loader ) );
	girl->SetPos( grid.ConvertToScreen( GridPos( 10, 5 ) ) );
	girl_controller->Attach( girl );
	
	girls.push_back( girl );
}
void World::KillGirl( boost::shared_ptr<Girl> girl )
{
	girl_controller->Detach( girl );
	std::remove( girls.begin(), girls.end(), girl );
}

void World::InitTiles( boost::shared_ptr<SpriteLoader> spr_loader )
{
	int n = 0;
	for( size_t x = 0; x < grid.GetColumns(); ++x ) {
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
