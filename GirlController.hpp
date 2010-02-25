#pragma once

#include "Controller.hpp"

class Girl;

class GirlController : public Controller {
public:
	GirlController( boost::shared_ptr<Girl> girl );
	
	void Update( float dt );
private:
	boost::shared_ptr<Girl> girl;
	HgeObj hge;
};
