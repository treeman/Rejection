#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"

class Dude {
public:
	Dude();

	void Update( float dt );
	void Render();
private:
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
};
