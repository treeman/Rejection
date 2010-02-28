#pragma once

#include "Tile.hpp"
#include "Sprite.hpp"

//you have to define the desired grasses
class GrassTile : public Tile {
public:
	GrassTile( Vec2D pos );
	virtual ~GrassTile() { }
	
	void Reset();
	
	void WalkOver();
	bool IsSeeThrough();
	bool IsWalkable();
	
	bool IsDark() { return is_dark; }
	
	void Update( float dt );
	void Render();
protected:
	boost::shared_ptr<Sprite> lvl1_spr;
	boost::shared_ptr<Sprite> lvl2_spr;
	boost::shared_ptr<Sprite> lvl3_spr;
	
	boost::shared_ptr<Sprite> curr_spr;
	
	float timer;
	bool is_dark;
	
	void PlayWalk();
	EffectObj walk_eff;
	
	HgeObj hge;
};

class DarkGrassTile : public GrassTile {
public:
	DarkGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader );
};

class LightGrassTile : public GrassTile {
public:
	LightGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader );
};

class GeekDarkGrassTile : public GrassTile {
public:
	GeekDarkGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader );
};

class GeekLightGrassTile : public GrassTile {
public:
	GeekLightGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader );
};
