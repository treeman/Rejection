#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/InputHandler.hpp"

class GameComplete : public Tree::InputHandler {
public:
	GameComplete();
	
	bool HandleEvent( hgeInputEvent &event );
	
	void Play( bool success );
	bool IsActive();
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<hgeSprite> shade;
	
	bool is_active;
	bool success;
};
