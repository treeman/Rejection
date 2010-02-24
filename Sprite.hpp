#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Lua/Lua.hpp"
#include "Tree/Errorhandling.hpp"

//Shall become a helper for managing tex and sprites
//Should be able to load sprites and animes from lua

struct Sprite {
	Sprite( std::string file, float x, float y, float w, float h, DWORD color = 0 );

	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	DWORD color;
};

class SpriteLoader {
public:
	SpriteLoader();
	
	void Load( std::string lua_file ) throw( Error::lua_error & );
	
	boost::shared_ptr<Sprite> Get( std::string name );
private:
	typedef std::map<std::string, boost::shared_ptr<Sprite> > SpriteMap;
	SpriteMap sprite_map;
};
