#include "World.hpp"

#include <boost/foreach.hpp>

World::World( boost::shared_ptr<SpriteLoader> spr_loader ) : grid( 32, 32, 23, 32, 32, 17, spr_loader )
{
	dude.reset( new Dude( spr_loader ) );
	grid.GetTiles()[4][4]->Attach( dude );
}

boost::shared_ptr<Dude> World::GetDude()
{
	return dude;
}

void World::Update( float dt )
{
	dude->Update( dt );
	Grid::TileGrid tile_grid = grid.GetTiles();
	for( size_t x = 0; x < tile_grid.size(); ++x ) {
		for( size_t y = 0; y < tile_grid[x].size(); ++y ) {
			tile_grid[x][y]->Update( dt );
		}
	}
}
void World::Render()
{
	Grid::TileGrid tile_grid = grid.GetTiles();
	for( size_t x = 0; x < tile_grid.size(); ++x ) {
		for( size_t y = 0; y < tile_grid[x].size(); ++y ) {
			tile_grid[x][y]->Render( grid.ConvertXToScreen( x ), grid.ConvertYToScreen( y ) );
		}
	}
	
	dude->Render();
}
