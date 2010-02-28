#pragma once

#include "Trap.hpp"
#include "Sprite.hpp"

class BlowerTrap : public Trap {
public:
	BlowerTrap( boost::shared_ptr<SpriteLoader> spr_loader );
	
	void Render();
private:
	boost::shared_ptr<Sprite> spr;
};

class MagnetTrap : public Trap {
public:
	MagnetTrap( boost::shared_ptr<SpriteLoader> spr_loader );
	
	void Render();
private:
	boost::shared_ptr<Sprite> spr;
};
