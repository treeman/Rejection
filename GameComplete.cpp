#include "GameComplete.hpp"

GameComplete::GameComplete()
{
	shade.reset( new hgeSprite( 0, 0, 0, 800, 600 ) );
	shade->SetColor( 0x70000000 );
	
	is_active = false;
}

bool GameComplete::HandleEvent( hgeInputEvent &event )
{
	return false;
}

void GameComplete::Play( bool success )
{
	is_active = true;
}
bool GameComplete::IsActive()
{
	
}

void GameComplete::Update( float dt )
{
	
}
void GameComplete::Render()
{
	shade->Render(0,0);
}
