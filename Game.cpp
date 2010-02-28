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
	
	info_bar.reset( new InfoBar( spr_loader ) );
	info_bar->SetLife( 5 );
	world->AddListener( info_bar.get() );
	
	tracks.reset( new Tracks() );
	tracks->Play();
	
	game_complete.reset( new GameComplete( world.get() ) );
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
	
	if( game_complete->IsActive() ) {
		game_complete->HandleEvent( event );
	}
	else {
		dude_controller->HandleEvent( event );
	}
	
	return true;
}

void Game::Update( float dt )
{
	if( game_complete->IsActive() ) {
		game_complete->Update( dt );
	}
	else {
		dude_controller->Update( dt );
		world->Update( dt );
		
		if( world->GameComplete() ) {
			game_complete->Play( true );
		}
		else if( world->GameOver() ) {
			game_complete->Play( false );
		}
	}
}
void Game::Render()
{
	info_bar->Render();
	world->Render();
	
	if( game_complete->IsActive() ) {
		game_complete->Render();
	}
}
