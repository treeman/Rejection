#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/Rect.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Dator.hpp"
#include "Tile.hpp"
#include "Sprite.hpp"
#include "MovingObject.hpp"

class Dude : public Attachable, public MovingObject {
public:
	Dude( boost::shared_ptr<SpriteLoader> spr_loader );
	
	Tree::Rect Bounds() const;
	
	float GetSpeed();

	void Update( float dt );
	void Render();
private:
	typedef std::map<std::string, boost::shared_ptr<Sprite> > SpriteMap;
	SpriteMap spr_map;
	boost::shared_ptr<Sprite> curr_spr;
};
