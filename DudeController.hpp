#pragma once

#include "Controller.hpp"

class Dude;

class DudeController  : public Controller {
public:
	DudeController( boost::shared_ptr<Dude> dude );
	
	bool HandleEvent( hgeInputEvent &e );
	void Update( float dt );
private:
	boost::shared_ptr<Dude> dude;
	HgeObj hge;
};
