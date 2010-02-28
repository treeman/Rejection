#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/InputHandler.hpp"

class World;

class GameComplete : public Tree::InputHandler {
public:
	GameComplete( World *world );
	
	bool HandleEvent( hgeInputEvent &event );
	
	void Play( bool success );
	bool IsActive();
	
	void Update( float dt );
	void Render();
private:
	void NewGame();
	void Exit();

	boost::shared_ptr<hgeSprite> shade;
	
	bool is_active;
	bool success;
	
	int pos;
	
	World *world;
};
