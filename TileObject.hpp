#pragma once

#include "Tree/Vec2D.hpp"
#include "Tree/Rect.hpp"

class TileObject {
public:
	virtual ~TileObject() { }
	
	virtual Tree::Rect Bounds() const;
	
	virtual bool IsWalkable() { return true; }
	virtual bool IsSeeThrough() { return true; }
	
	virtual void FaceLeft() { }
	virtual void FaceRight() { }
	virtual void FaceUp() { }
	virtual void FaceDown() { }
	
	void SetPos( Vec2D p ) { pos = p; }
	void SetXPos( float x ) { pos.x = x; }
	void SetYPos( float y ) { pos.y = y; }
	Vec2D GetPos() const { return pos; }
	
	virtual void Update( float dt ) { }
	virtual void Render() = 0;
protected:
	Vec2D pos;
};
