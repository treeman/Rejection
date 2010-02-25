#include "Grid.hpp"
#include "GrassTiles.hpp"

Grid::Grid( int _x, int  _box_w, int _columns, int  _y, int  _box_h, int _rows, boost::shared_ptr<SpriteLoader> spr_loader  ) :
	x( _x), box_w( _box_w ), columns( _columns ), y( _y ), box_h( _box_h ), rows( _rows )
{
	int n = 0;
	for( size_t x = 0; x < columns; ++x ) {
		Tiles column;
		for( size_t y = 0; y < rows; ++y, ++n ) {
			TilePtr tile;
			if( n % 2 == 0 ) {
				tile.reset( new LightGrassTile( ConvertToScreen( GridPos( x, y ) ), spr_loader ) );
			}
			else {
				tile.reset( new DarkGrassTile( ConvertToScreen( GridPos( x, y ) ), spr_loader ) );
			}
			column.push_back( tile );
		}
		tiles.push_back( column );
	}
}

float Grid::ConvertXToScreen( int x_pos )
{
	return x + x_pos * box_w;
}
float Grid::ConvertYToScreen( int y_pos )
{
	return y + y_pos * box_h;
}
	
Vec2D Grid::ConvertToScreen( GridPos p )
{
	return Vec2D( x + p.x * box_w, y + p.y * box_h );
}
GridPos Grid::ConvertToGrid( Vec2D p )
{
	return GridPos( 
		math::clip( (int)(( p.x - x ) / box_w), 0, columns - 1 ), 
		math::clip( (int)(( p.y - y ) / box_h), 0, rows - 1 )
	);
}

bool Grid::IsWalkAble( int x, int y )
{
	if( !IsValid( x, y ) ) return false;
	else return tiles[x][y]->IsWalkable();
}

bool Grid::IsValid( int x, int y )
{
	return x < 0 || x > columns - 1 || y < 0 || y > rows - 1;
}
