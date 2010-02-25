#include "World.hpp"

#include <boost/foreach.hpp>
#include "Tree/Log.hpp"

World::World( boost::shared_ptr<SpriteLoader> spr_loader ) : grid( 32, 32, 23, 32, 32, 17, spr_loader )
{
	dude.reset( new Dude( spr_loader ) );
	dude->SetPos( grid.ConvertToScreen( GridPos( 5, 0 ) ) );
	
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
	dude->Update( dt );
	
	Grid::TileGrid tile_grid = grid.GetTiles();
	
	//a grid pos will be a valid array index
	const GridPos dude_gpos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
	
	//check dude stop targets
	if( dude->WantsStop() ) 
	{
		if( dude->WantsLeft() ) 
		{
			//if we can walk to the left and if we're intersecting with it
			if( grid.IsWalkable( dude_gpos.x - 1, dude_gpos.y ) &&
				tile_grid[dude_gpos.x - 1][dude_gpos.y]->Bounds().Intersects( dude->Bounds() ) ) 
			{
				dude->StopAt( grid.ConvertToScreen( GridPos( dude_gpos.x - 1, dude_gpos.y ) ) );
			}
			//else stop it immediatly
			else {
				dude->StopAt( grid.ConvertToScreen( dude_gpos ) );
			}
		}
		else if( dude->WantsRight() ) 
		{
			//same but to the right
			if( grid.IsWalkable( dude_gpos.x + 1, dude_gpos.y ) &&
				tile_grid[dude_gpos.x + 1][dude_gpos.y]->Bounds().Intersects( dude->Bounds() ) ) 
			{
				dude->StopAt( grid.ConvertToScreen( GridPos( dude_gpos.x + 1, dude_gpos.y ) ) );
			}
			else {
				dude->StopAt( grid.ConvertToScreen( dude_gpos ) );
			}
		}
		//up and down compare to left and right
		else if( dude->WantsUp() ) 
		{
			if( grid.IsWalkable( dude_gpos.x, dude_gpos.y - 1 ) &&
				tile_grid[dude_gpos.x][dude_gpos.y - 1]->Bounds().Intersects( dude->Bounds() ) ) 
			{
				dude->StopAt( grid.ConvertToScreen( GridPos( dude_gpos.x, dude_gpos.y - 1 ) ) );
			}
			else {
				dude->StopAt( grid.ConvertToScreen( dude_gpos ) );
			}
		}
		else if( dude->WantsDown() ) 
		{
			if( grid.IsWalkable( dude_gpos.x, dude_gpos.y + 1 ) &&
				tile_grid[dude_gpos.x][dude_gpos.y + 1]->Bounds().Intersects( dude->Bounds() ) ) 
			{
				dude->StopAt( grid.ConvertToScreen( GridPos( dude_gpos.x, dude_gpos.y + 1 ) ) );
			}
			else {
				dude->StopAt( grid.ConvertToScreen( dude_gpos ) );
			}
		}
	}
	
	//check and correct dude to the world borders
	CheckWorldBounds( dude );
	
	for( size_t x = 0; x < tile_grid.size(); ++x ) {
		for( size_t y = 0; y < tile_grid[x].size(); ++y ) {
			const Grid::TilePtr tile = tile_grid[x][y];
			
			if( dude->Bounds().Intersects( tile->Bounds() ) )
			{
				tile->WalkOver();
			}
			tile->Update( dt );
		}
	}
}
void World::Render()
{
	float mx, my;
	hge->Input_GetMousePos( &mx, &my );
	
	Grid::TileGrid tile_grid = grid.GetTiles();
	for( size_t x = 0; x < tile_grid.size(); ++x ) {
		for( size_t y = 0; y < tile_grid[x].size(); ++y ) {
			const Tree::Rect r = tile_grid[x][y]->Bounds();
			
			tile_grid[x][y]->Render();
			if( show_bounds->Val() ) {
				hgeh::render_rect( hge, r.x1, r.y1, r.x2, r.y2, 0xff666666 );
			}
		}
	}
	
	dude->Render();
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

void World::CheckWorldBounds( boost::shared_ptr<MovingObject> o )
{
	float x1, y1, x2, y2;
	grid.GetBounds( x1, y1, x2, y2 );
	
	const Tree::Rect b(
		o->GetPos().x,
		o->GetPos().y,
		32, 32 );
	
	//you just love the magic numbers eh?
	if( b.x1 < x1 ) o->SetXPos( x1 );
	if( b.x2 > x2 ) o->SetXPos( x2 - b.Width() );
	
	if( b.y1 < y1 ) o->SetYPos( y1 );
	if( b.y2 > y2 ) o->SetYPos( y2 - b.Height() );
}
