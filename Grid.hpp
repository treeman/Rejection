#pragma once

#include <vector>

#include "Tree/Vec2D.hpp"

#include "Tile.hpp"
#include "Sprite.hpp"

struct GridPos {
	GridPos( int _x = 0, int _y = 0 ) :
		x( _x), y( _y) { }
	int x, y;
};

class Grid {
public:
	Grid( int x, int box_w, int columns, int y, int box_h, int rows, boost::shared_ptr<SpriteLoader> spr_loader );
	
	float ConvertXToScreen( int x_pos );
	float ConvertYToScreen( int y_pos );
	
	Vec2D ConvertToScreen( GridPos p );
	GridPos ConvertToGrid( Vec2D p );
	
	int GetColumns() { return columns; }
	int GetRows() { return rows; }
	
	bool IsWalkable( int x, int y );
	
	void GetBounds( float &x1, float &y1, float &x2, float &y2 ); 
	
	typedef boost::shared_ptr<Tile> TilePtr;
	typedef std::vector<TilePtr> Tiles;
	typedef std::vector<Tiles> TileGrid;
	
	TileGrid &GetTiles() { return tiles; }
	
	bool IsValid( int x, int y );
private:
	int x, y;
	int box_w, box_h;
	int columns, rows;
	
	TileGrid tiles;
};
