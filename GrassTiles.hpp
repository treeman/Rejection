#pragma once

#include "Tile.hpp"
#include "Sprite.hpp"

//you have to define the desired grasses
class GrassTile : public Tile {
public:
	GrassTile();
	virtual ~GrassTile() { }
	
	void Update( float dt );
	void Render( float x, float y );
protected:
	boost::shared_ptr<Sprite> lvl1_spr;
	boost::shared_ptr<Sprite> lvl2_spr;
	boost::shared_ptr<Sprite> lvl3_spr;
	
	boost::shared_ptr<Sprite> curr_spr;
	
	float timer;
};

class DarkGrassTile : public GrassTile {
public:
	DarkGrassTile( boost::shared_ptr<SpriteLoader> spr_loader );
};

class LightGrassTile : public GrassTile {
public:
	LightGrassTile( boost::shared_ptr<SpriteLoader> spr_loader );
};
