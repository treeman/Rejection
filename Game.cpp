#include "Game.hpp"
#include "Tree/Game.hpp"
#include "Tree/Log.hpp"

#include <boost/foreach.hpp>

Game::Game() : world( new World() ), 
	dude_controller( new DudeController( world->GetDude() ) )
{
	
}
	
bool Game::HandleEvent( hgeInputEvent &event )
{
	if( event.type == INPUT_KEYDOWN ) {
		switch( event.key ) {
			case HGEK_F10: Tree::Game::Instance()->Exit(); break;
		}
	}
	
	dude_controller->HandleEvent( event );
	
	return true;
}

void Game::Update( float dt )
{
	dude_controller->Update( dt );
	world->Update( dt );
}
void Game::Render()
{
	world->Render();
}
