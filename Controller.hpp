#pragma once

#include "Tree/InputHandler.hpp"

class Controller : public Tree::InputHandler {
public:
	virtual ~Controller() { }
	
	virtual bool HandleEvent( hgeInputEvent &e ) { };
	virtual void Update( float dt ) { }
};
