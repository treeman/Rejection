#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/Rect.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Dator.hpp"
#include "Sprite.hpp"
#include "Person.hpp"

enum VisionObject {
	VISION_FREE,
	VISION_OBSUCRED,
	VISION_DUDE,
	VISION_SELF
};

class Girl : public Person {
public:
	Girl( boost::shared_ptr<SpriteLoader> spr_loader );
	
	float GetSpeed();
	
	void FaceLeft();
	void FaceRight();
	void FaceUp();
	void FaceDown();
	
	typedef std::vector<std::vector<int> > Vision;
	void SetVision( Vision v ) { vision = v; }
	Vision GetVision() { return vision; }

	void Update( float dt );
	void Render();
private:
	typedef std::map<std::string, boost::shared_ptr<Sprite> > SpriteMap;
	SpriteMap spr_map;
	boost::shared_ptr<Sprite> curr_spr;
	
	Vision vision;
	
	boost::shared_ptr<Tree::Dator<bool> > debug_girl;
	boost::shared_ptr<hgeFont> fnt;
};
