#pragma once

#include "Controller.hpp"

class Girl;

class GirlController : public Controller {
public:
	GirlController();
	
	void Attach( boost::shared_ptr<Girl> girl );
	void Detach( boost::shared_ptr<Girl> girl );
	
	void Update( float dt );
private:
	void UpdateGirl( boost::shared_ptr<Girl> girl, float dt );

	typedef std::vector<boost::shared_ptr<Girl> > Girls;
	Girls girls;
	
	HgeObj hge;
};
