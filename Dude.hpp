#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tile.hpp"
#include "Sprite.hpp"

class Dude : public Attachable {
public:
	Dude();

	void Update( float dt );
	void Render();
private:
	typedef std::map<std::string, boost::shared_ptr<Sprite> > SpriteMap;
	SpriteMap spr_map;
	boost::shared_ptr<Sprite> curr_spr;
	
	boost::shared_ptr<SpriteLoader> spr_loader;
};
