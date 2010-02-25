#pragma once

#include "Hge/Hge.hpp"

#include "Grid.hpp"
#include "Dude.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Dator.hpp"

class World {
public:
	World( boost::shared_ptr<SpriteLoader> spr_loader );
	
	boost::shared_ptr<Dude> GetDude();
	
	void Update( float dt );
	void Render();
private:
	void CheckWorldBounds( boost::shared_ptr<MovingObject> o );
	
	Grid grid;
	
	boost::shared_ptr<Dude> dude;
	boost::shared_ptr<hgeFont> fnt;
	
	boost::shared_ptr<Tree::Dator<bool> > show_mouse_grid;
	boost::shared_ptr<Tree::Dator<bool> > show_bounds;
	
	HgeObj hge;
	
	boost::shared_ptr<Tree::Dator<bool> > debug_dude;
};
