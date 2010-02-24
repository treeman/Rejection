#pragma once

#include "Tile.hpp"
#include "Sprite.hpp"

//you have to define the desired grasses
class GrassTile : public Tile {
public:
	GrassTile( Vec2D pos );
	virtual ~GrassTile() { }
	
	void WalkOver();
	
	void Update( float dt );
	void Render();
protected:
	boost::shared_ptr<Sprite> lvl1_spr;
	boost::shared_ptr<Sprite> lvl2_spr;
	boost::shared_ptr<Sprite> lvl3_spr;
	
	boost::shared_ptr<Sprite> curr_spr;
	
	float timer;
};

class DarkGrassTile : public GrassTile {
public:
	DarkGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader );
};

class LightGrassTile : public GrassTile {
public:
	LightGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader );
};
