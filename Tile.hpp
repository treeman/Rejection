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
	
	boost::shared_ptr<Attachable> Attachment();
	
	bool Attach( boost::shared_ptr<Attachable> a );
	void Detach();
	
	void Render( float x, float y );
private:
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	
	boost::shared_ptr<Attachable> attachment;
};
