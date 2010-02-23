#pragma once

#include "Tile.hpp"

class DarkGrassTile : public Tile {
public:
	DarkGrassTile() : tex( "gfx/darkgrass.png" ), spr( new hgeSprite( tex, 0, 0, 32, 32 ) ) { }
	
	void Render( float x, float y ) { spr->Render( (int)x, (int)y ); }
protected:
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
};

class LightGrassTile : public Tile {
public:
	LightGrassTile() : tex( "gfx/grass.png" ), spr( new hgeSprite( tex, 0, 0, 32, 32 ) ) { }
	
	void Render( float x, float y ) { spr->Render( (int)x, (int)y ); }
protected:
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
};
