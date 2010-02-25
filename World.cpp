#include "World.hpp"

#include <boost/foreach.hpp>
#include "Tree/Log.hpp"

World::World( boost::shared_ptr<SpriteLoader> spr_loader ) : grid( 32, 32, 23, 32, 32, 17, spr_loader )
{
	dude.reset( new Dude( spr_loader ) );
	dude->SetPos( Vec2D( 320, 320 ) );
	
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
	
//	if( dude->WantsLeft() || dude->WantsRight() ) {
////		ConstrainDudeY();
//	}
//	else if( dude->WantsUp() || dude->WantsDown() ) {
////		ConstrainDudeX();
//	}
//	else {
////		ConstrainDudeTile();
//	}
	
	const GridPos dude_gpos = grid.ConvertToGrid( dude->GetPos() );
	GridPos dude_next_pos;
	if( dude->WantsLeft() ) { dude_next_pos = GridPos( dude_gpos.x - 1, dude_gpos.y ); }
	else if( dude->WantsRight() ) { dude_next_pos = GridPos( dude_gpos.x + 1, dude_gpos.y ); }
	else if( dude->WantsUp() ) { dude_next_pos = GridPos( dude_gpos.x, dude_gpos.y - 1 ); }
	else if( dude->WantsDown() ) { dude_next_pos = GridPos( dude_gpos.x, dude_gpos.y + 1 ); }
	
	if( dude->WantsStop() ) {
		
		//a grid pos will be a valid array index
		
		if( dude->WantsLeft() ) 
		{
			//checks if the tile to the left isn't empty (dude is to the far left) and
			//if it intersects with the tile to the left, in which case it stops at the
			//tile to the left
			if( dude_gpos.x >= 0 &&
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
			//-1 to get array index
			if( dude_gpos.x <= grid.GetColumns() - 1 &&
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
			if( dude_gpos.y >= 0 &&
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
			if( dude_gpos.y <= grid.GetRows() + 1 &&
				tile_grid[dude_gpos.x][dude_gpos.y + 1]->Bounds().Intersects( dude->Bounds() ) ) 
			{
				dude->StopAt( grid.ConvertToScreen( GridPos( dude_gpos.x, dude_gpos.y + 1 ) ) );
			}
			else {
				dude->StopAt( grid.ConvertToScreen( dude_gpos ) );
			}
		}
	}
	
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
		hgeh::render_rect( hge, r.x1, r.y1, r.x2, r.y2, 0xff999999 );
	}
	
	if( show_mouse_grid->Val() ) {
		fnt->SetColor( 0xffffffff );
		
		GridPos grid_pos = grid.ConvertToGrid( Vec2D( mx, my ) );
		fnt->printf( 100, 5, HGETEXT_LEFT, "%i, %i", grid_pos.x, grid_pos.y );
	}
	
	if( debug_dude->Val() ) {
		GridPos grid_pos = grid.ConvertToGrid( dude->Bounds().GetCenter() );
		fnt->printf( 460, 5, HGETEXT_LEFT, "dude_grid:%i,%i", grid_pos.x, grid_pos.y );
	}
}

void World::ConstrainDudeX()
{
	const Vec2D pos = dude->Bounds().GetCenter();
	const GridPos dude_gpos = grid.ConvertToGrid( pos );
	const Vec2D new_pos = Vec2D( grid.ConvertXToScreen( dude_gpos.x ), pos.y );
	dude->SetPos( new_pos );
	dude->SetXVel( 0 );
	L_ << "constraining x pos:" << pos.x << "," << pos.y;
	L_ << "gpos:" << dude_gpos.x << "," << dude_gpos.y;
	L_<< "new:" << new_pos.x << "," << new_pos.y;
}
void World::ConstrainDudeY()
{
	const Vec2D pos = dude->Bounds().GetCenter();
	const GridPos dude_gpos = grid.ConvertToGrid( pos );
	const Vec2D new_pos = Vec2D( pos.x, grid.ConvertYToScreen( dude_gpos.y ) );
	dude->SetPos( new_pos );
	dude->SetYVel( 0 );
	L_<< "constraining y pos:" << pos.x << "," << pos.y;
	L_<< "gpos:" << dude_gpos.x << "," << dude_gpos.y;
	L_<< "new:" << new_pos.x << "," << new_pos.y;
}
void World::ConstrainDudeTile()
{
	const Vec2D pos = dude->Bounds().GetCenter();
	const GridPos dude_gpos = grid.ConvertToGrid( pos );
	const Vec2D new_pos = Vec2D( grid.ConvertToScreen( dude_gpos ) );
	dude->SetPos( new_pos );
}
