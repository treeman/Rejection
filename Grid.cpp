#include "Grid.hpp"

Grid::Grid( int _x, int  _box_w, int _columns, int  _y, int  _box_h, int _rows ) :
	x( _x), box_w( _box_w ), columns( _columns ), y( _y ), box_h( _box_h ), rows( _rows )
{
	for( size_t x = 0; x < columns; ++x ) {
		Tiles column;
		for( size_t y = 0; y < rows; ++y ) {
			TilePtr tile( new Tile() );
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
	return GridPos( (int)(( p.x - x ) / box_w), (int)(( p.y - y ) / box_h ) );
}
