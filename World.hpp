#pragma once

#include "Grid.hpp"
#include "Dude.hpp"

class World {
public:
	World();
	
	boost::shared_ptr<Dude> GetDude();
	
	void Update( float dt );
	void Render();
private:
	Grid grid;
	
	boost::shared_ptr<Dude> dude;
};
