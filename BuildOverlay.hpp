#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Tree/InputHandler.hpp"
#include "Sprite.hpp"
#include "TrapFactory.hpp"

class World;

class BuildOverlay : public Tree::InputHandler {
public:
	BuildOverlay( World *world, boost::shared_ptr<SpriteLoader> spr_loader, Vec2D pos );
	
	bool HandleEvent( hgeInputEvent &event );
	
	bool IsActive();
	void Activate();
	void Deactivate();
	
	void Update( float dt );
	void Render();
private:
	void Left();
	void Right();
	void Action();

	boost::shared_ptr<TrapFactory> trap_factory;
	
	typedef std::vector<boost::shared_ptr<Trap> > Traps;
	Traps traps;
	
	boost::shared_ptr<Sprite> build_background;
	boost::shared_ptr<hgeSprite> trap_shade;
	boost::shared_ptr<Sprite> trap_highlight;
	boost::shared_ptr<Sprite> cancel;
	
	boost::shared_ptr<hgeFont> fnt;
	
	World *world;
	bool is_active;
	
	int selection_pos;
	
	Vec2D pos;
};
