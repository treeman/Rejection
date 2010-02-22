#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/GameState.hpp"

#include "World.hpp"

class Game : public Tree::GameState {
public:
	Game();
	
	bool HandleEvent( hgeInputEvent &e );
	
	void Update( float dt );
	void Render();
private:
	HgeObj hge;
	
	boost::shared_ptr<World> world;
};
