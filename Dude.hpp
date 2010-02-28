#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/Rect.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Dator.hpp"
#include "Sprite.hpp"
#include "Person.hpp"

class Dude : public Person {
public:
	Dude( boost::shared_ptr<SpriteLoader> spr_loader );
	
	float GetSpeed();
	
	void FaceLeft();
	void FaceRight();
	void FaceUp();
	void FaceDown();
	
	bool WantsAction();
	void DoAction();
	void CancelAction();

	void Update( float dt );
	void Render();
private:
	typedef std::map<std::string, boost::shared_ptr<Sprite> > SpriteMap;
	SpriteMap spr_map;
	boost::shared_ptr<Sprite> curr_spr;
	
	bool wants_action;
	
	boost::shared_ptr<Tree::Dator<bool> > debug_dude;
	boost::shared_ptr<hgeFont> fnt;
};
