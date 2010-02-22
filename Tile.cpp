#include "Tile.hpp"

Tile::Tile() : tex( "gfx/grass.png" ), spr( new hgeSprite( tex, 0, 0, 32, 32 ) )
{
	
}
	
void Tile::Render( float x, float y )
{
	spr->Render( (int)x, (int)y );
}
