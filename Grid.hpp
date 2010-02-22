#pragma once

#include <cstring>
#include "Tree/Vec2D.hpp"

struct GridPos {
	GridPos( size_t _x = 0, size_t _y = 0 ) :
		x( _x), y( _y) { }
	size_t x, y;
};

class Grid {
public:
	Grid( int x, int box_w, size_t columns, int y, int box_h, size_t rows );
	
	Vec2D ConvertToScreen( GridPos p );
	GridPos ConvertToGrid( Vec2D p );
private:
	int x, y;
	int box_w, box_h;
	size_t columns, rows;
};
