#pragma once

#include "Trap.hpp"
#include "Sprite.hpp"
#include "Tree/Timer.hpp"

class BlowerTrap : public Trap {
public:
	BlowerTrap( boost::shared_ptr<SpriteLoader> spr_loader );
	
	bool IsWalkable();
	bool IsSeeThrough();
	
	int GetBlowLength();
	Vec2D GetBlowDir();
	
	void Activate();
	void Deactivate();
	
	bool IsActive();
	
	void Render();
private:
	boost::shared_ptr<Sprite> spr;
	Tree::Timer t;
};

class MagnetTrap : public Trap {
public:
	MagnetTrap( boost::shared_ptr<SpriteLoader> spr_loader );
	
	bool IsWalkable();
	bool IsSeeThrough();
//	
//	int GetBlowLength();
//	Vec2D GetBlowDir();
	
	void Render();
private:
	boost::shared_ptr<Sprite> spr;
	Tree::Timer t;
};

class PressurePad : public Trap {
public:
	PressurePad( boost::shared_ptr<SpriteLoader> spr_loader );
	
	bool IsWalkable();
	bool IsSeeThrough();
	
	int GetActivationRadius();
	void Activate();
	void Deactivate();
	
	bool IsActive();
	
	void WalkOver();
	
	void Render();
private:
	boost::shared_ptr<Sprite> spr;
	Tree::Timer t;
};
