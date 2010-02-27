#include "Game.hpp"
#include "Tree/Game.hpp"
#include "Tree/Log.hpp"
#include "Tweaks.hpp"

#include <boost/foreach.hpp>

Game::Game() : spr_loader( new SpriteLoader() )
{
	spr_loader->Load( "sprites.lua" );
	world.reset( new World( spr_loader ) );
	dude_controller.reset( new DudeController( world->GetDude() ) );
}
Game::~Game()
{
	//destroy tweaks
	Tweaks::Instance()-> Destroy();
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
