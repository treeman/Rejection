#include "World.hpp"

#include <boost/foreach.hpp>

World::World( boost::shared_ptr<SpriteLoader> spr_loader ) : grid( 32, 32, 23, 32, 32, 17, spr_loader )
{
	dude.reset( new Dude( spr_loader ) );
	dude->SetPos( Vec2D( 320, 320 ) );
	
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	show_mouse_grid.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "mouse_grid_pos_show", boost::weak_ptr<Tree::BaseDator>( show_mouse_grid ) );
	
	show_bounds.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "bounds_show", boost::weak_ptr<Tree::BaseDator>( show_bounds ) );
}

boost::shared_ptr<Dude> World::GetDude()
{
	return dude;
}

void World::Update( float dt )
{
	dude->Update( dt );
	const GridPos dude_gpos = grid.ConvertToGrid( dude->GetPos() );
	Grid::TileGrid tile_grid = grid.GetTiles();
	
	for( size_t x = 0; x < tile_grid.size(); ++x ) {
		for( size_t y = 0; y < tile_grid[x].size(); ++y ) {
			const Grid::TilePtr tile = tile_grid[x][y];
			
//			if( //dude_gpos.x <= x && dude_gpos.y <= y && 
//				dude->Bounds().Intersects( tile->Bounds() ) )
//			{
				tile->WalkOver();
//			}
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
			
			if( r.IsOver( mx, my ) ) continue;
			
			tile_grid[x][y]->Render();
//			if( show_bounds->Val() ) {
//				hgeh::render_rect( hge, r.x1, r.y1, r.x2, r.y2, 0xff666666 );
//			}
		}
	}
	
	dude->Render();
	if( show_bounds->Val() ) {
		const Tree::Rect r = dude->Bounds();
		hgeh::render_rect( hge, r.x1, r.y1, r.x2, r.y2, 0xff999999 );
	}
	
	if( show_mouse_grid->Val() ) {
		fnt->SetColor( 0xffffffff );
		
		GridPos grid_pos = grid.ConvertToGrid( Vec2D( mx, my ) );
		fnt->printf( 100, 5, HGETEXT_LEFT, "%i, %i", grid_pos.x, grid_pos.y );
	}
}
