#pragma once

#include "MovingObject.hpp"

enum VisionObject {
	VISION_FREE,
	VISION_OBSUCRED,
	VISION_DUDE,
	VISION_SELF,
	VISION_INVALID
};

class Person : public MovingObject {
public:
	virtual ~Person() { }
	
	typedef std::vector<std::vector<int> > Vision;
	void SetVision( Vision v ) { vision = v; }
	Vision GetVision() { return vision; }
	
	virtual void Update( float dt ) = 0;
	virtual void Render() = 0;
	
protected:
	Vision vision;
};
