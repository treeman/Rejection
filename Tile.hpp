#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/Vec2D.hpp"
#include "Tree/Rect.hpp"

#include "TileObject.hpp"

class Tile {
public:
	Tile( Vec2D pos );
	virtual ~Tile() { }
	
	boost::shared_ptr<TileObject> Attachment();
	
	bool Attach( boost::shared_ptr<TileObject> a );
	void Detach();
	
	virtual void Reset() { }
	
	virtual void WalkOver() { }
	virtual bool IsWalkable();
	virtual bool IsSeeThrough();
	
	void SetPos( Vec2D p ) { pos = p; }
	Vec2D GetPos() const { return pos; }
	
	virtual Tree::Rect Bounds() const;
	
	virtual void Update( float ) { }
	virtual void Render() = 0;
protected:
	boost::shared_ptr<TileObject> attachment;
	Vec2D pos;
};
