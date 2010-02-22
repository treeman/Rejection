#include "Dude.hpp"

Dude::Dude() : tex( "gfx/geek.png" ), spr( new hgeSprite( tex, 0, 0, 32, 32 ) )
{
	
}

void Dude::Update( float dt )
{
	
}
void Dude::Render()
{
	spr->Render( 320, 320 );
}
