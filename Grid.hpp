#pragma once

#include <vector>

#include "Tree/Vec2D.hpp"

#include "Sprite.hpp"

struct GridPos {
	GridPos( int _x = 0, int _y = 0 ) :
		x( _x), y( _y) { }
		
	bool operator == ( const GridPos &g ) const { return x == g.x && y == g.y; }
	bool operator != ( const GridPos &g ) const { return !(*this == g); }
	
	int x, y;
};

class Grid {
public:
	Grid( int x, int box_w, int columns, int y, int box_h, int rows );
	
	float ConvertXToScreen( int x_pos ) const;
	float ConvertYToScreen( int y_pos ) const;
	
	Vec2D ConvertToScreen( GridPos p ) const;
	GridPos ConvertToGrid( Vec2D p ) const;
	
	int GetColumns() const { return columns; }
	int GetRows() const { return rows; }
	
	void GetBounds( float &x1, float &y1, float &x2, float &y2 ) const;
private:
	int x, y;
	int box_w, box_h;
	int columns, rows;
};
