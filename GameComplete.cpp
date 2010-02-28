#include "GameComplete.hpp"
#include "World.hpp"
#include "Tree/Game.hpp"

GameComplete::GameComplete( World *w ) : world( w )
{
	shade.reset( new hgeSprite( 0, 0, 0, 800, 600 ) );
	shade->SetColor( 0x70000000 );
	
	is_active = false;
	
	pos = 0;
}

bool GameComplete::HandleEvent( hgeInputEvent &e )
{
	if( e.type == INPUT_KEYDOWN ) {
		switch( e.key ) {
			case HGEK_LEFT:
				--pos;
				if( pos < 0 ) pos = 0;
				break;
			case HGEK_RIGHT:
				++pos;
				if( pos > 1 ) pos = 1;
				break;
			case HGEK_ENTER:
				if( pos == 0 ) NewGame();
				else if( pos == 1 ) Exit();
				is_active = false;
				break;
		}
	}
	
	return false;
}

void GameComplete::Play( bool success )
{
	is_active = true;
}
bool GameComplete::IsActive()
{
	return is_active;
}

void GameComplete::Update( float dt )
{
	
}
void GameComplete::Render()
{
	shade->Render(0,0);
}

void GameComplete::NewGame()
{
	world->NewGame();
}
void GameComplete::Exit()
{
	Tree::Game::Instance()->Exit();
}
