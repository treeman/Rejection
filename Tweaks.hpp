#pragma once

#include <string>
#include <map>

#include "Tree/Singleton.hpp"

#define TWEAKS Tweaks::Instance()

class Tweaks : public Tree::Singleton<Tweaks> {
public:
	Tweaks();
	
	float GetFloat( std::string s );
private:
	typedef std::map<std::string, float> FloatMap;
	FloatMap floats;
};
