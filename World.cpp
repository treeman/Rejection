#include "World.hpp"

#include <boost/foreach.hpp>

World::World() : grid( 32, 32, 23, 32, 32, 17 )
{
	
}
void World::Update( float dt )
{
	
}
void World::Render()
{
	Grid::TileGrid tile_grid = grid.GetTiles();
	for( size_t x = 0; x < tile_grid.size(); ++x ) {
		for( size_t y = 0; y < tile_grid[x].size(); ++y ) {
			tile_grid[x][y]->Render( grid.ConvertXToScreen( x ), grid.ConvertYToScreen( y ) );
		}
	}
}
