#include "Grid.hpp"

Grid::Grid( int _x, int  _box_w, int _columns, int  _y, int  _box_h, int _rows ) :
	x( _x), box_w( _box_w ), y( _y ), box_h( _box_h ), columns( _columns ), rows( _rows )
{
	
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

void Grid::GetBounds( float &x1, float &y1, float &x2, float &y2 )
{
	x1 = x; y1 = y;
	x2 = x + columns * box_w;
	y2 = y + rows * box_h;
}
