#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/GameState.hpp"

#include "World.hpp"
#include "DudeController.hpp"

class Game : public Tree::GameState {
public:
	Game();
	~Game();
	
	bool HandleEvent( hgeInputEvent &e );
	
	void Update( float dt );
	void Render();
private:
	HgeObj hge;
	
	boost::shared_ptr<SpriteLoader> spr_loader;
	boost::shared_ptr<World> world;
	boost::shared_ptr<Controller> dude_controller;
};
