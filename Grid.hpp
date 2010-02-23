#pragma once

#include <vector>

#include "Tree/Vec2D.hpp"

#include "Tile.hpp"

struct GridPos {
	GridPos( int _x = 0, int _y = 0 ) :
		x( _x), y( _y) { }
	int x, y;
};

class Grid {
public:
	Grid( int x, int box_w, int columns, int y, int box_h, int rows );
	
	float ConvertXToScreen( int x_pos );
	float ConvertYToScreen( int y_pos );
	
	Vec2D ConvertToScreen( GridPos p );
	GridPos ConvertToGrid( Vec2D p );
	
	typedef boost::shared_ptr<Tile> TilePtr;
	typedef std::vector<TilePtr> Tiles;
	typedef std::vector<Tiles> TileGrid;
	
	TileGrid &GetTiles() { return tiles; }
private:
	int x, y;
	int box_w, box_h;
	int columns, rows;
	
	TileGrid tiles;
};
