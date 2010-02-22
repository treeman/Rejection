#pragma once

#include "Grid.hpp"

class World {
public:
	World();
	
	void Update( float dt );
	void Render();
private:
	Grid grid;
};
