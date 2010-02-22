#include "Grid.hpp"

Grid::Grid( int _x, int  _box_w, size_t _columns, int  _y, int  _box_h, size_t _rows ) :
	x( _x), box_w( _box_w ), columns( _columns ), y( _y ), box_h( _box_h ), rows( _rows )
{
	
}
	
Vec2D Grid::ConvertToScreen( GridPos p )
{
	return Vec2D( x + p.x * box_w, y + p.y * box_h );
}
GridPos Grid::ConvertToGrid( Vec2D p )
{
	return GridPos( (int)(( p.x - x ) / box_w), (int)(( p.y - y ) / box_h ) );
}
