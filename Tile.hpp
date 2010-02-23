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
	virtual ~Tile() { }
	
	boost::shared_ptr<Attachable> Attachment();
	
	bool Attach( boost::shared_ptr<Attachable> a );
	void Detach();
	
	virtual void Render( float x, float y ) = 0;
protected:
	boost::shared_ptr<Attachable> attachment;
};
