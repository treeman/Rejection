#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/Vec2D.hpp"

class Attachable {
public:
	virtual ~Attachable() { }
};

class Tile {
public:
	Tile();
	
	void Render( float x, float y );
private:
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
};
