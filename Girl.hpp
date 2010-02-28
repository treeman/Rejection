#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/Rect.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Dator.hpp"
#include "Sprite.hpp"
#include "Person.hpp"

class Girl : public Person {
public:
	Girl( boost::shared_ptr<SpriteLoader> spr_loader );
	
	float GetSpeed();
	
	void Kill() { can_kill = true; }
	bool CanKill() { return can_kill; }
	
	void FaceLeft();
	void FaceRight();
	void FaceUp();
	void FaceDown();

	void Update( float dt );
	void Render();
private:
	typedef std::map<std::string, boost::shared_ptr<Sprite> > SpriteMap;
	SpriteMap spr_map;
	boost::shared_ptr<Sprite> curr_spr;
	
	boost::shared_ptr<Tree::Dator<bool> > debug_girl;
	boost::shared_ptr<hgeFont> fnt;
	
	bool can_kill;
};
