#pragma once

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "Sprite.hpp"
#include "Trap.hpp"

class TrapFactory {
public:
	TrapFactory( boost::shared_ptr<SpriteLoader> spr_loader );
	
	typedef std::vector<TrapInfo> Traps;
	Traps GetTraps();
	
	boost::shared_ptr<Trap> CreateTrap( TrapInfo trap );
private:
	Traps traps;
	boost::shared_ptr<SpriteLoader> spr_loader;
};
