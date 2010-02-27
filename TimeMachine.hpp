#pragma once

#include <boost/shared_ptr.hpp>

#include "TileObject.hpp"
#include "Sprite.hpp"

class TimeMachine : public TileObject {
public:
	TimeMachine( boost::shared_ptr<SpriteLoader> spr_loader );
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<Sprite> spr;
};
