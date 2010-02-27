#pragma once

#include "Lua/Lua.hpp"
#include "Tree/Singleton.hpp"

#define TWEAKS Tweaks::Instance()

class Tweaks : public Tree::Singleton<Tweaks> {
public:
	Tweaks();
	
	LuaState Lua();
private:
	LuaState L;
};
