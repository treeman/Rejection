#include "Tile.hpp"

Tile::Tile() : tex( "gfx/grass.png" ), spr( new hgeSprite( tex, 0, 0, 32, 32 ) )
{
	
}

boost::shared_ptr<Attachable> Tile::Attachment()
{
	return attachment;
}

bool Tile::Attach( boost::shared_ptr<Attachable> a )
{
	if( attachment ) {
		attachment = a;
		return true;
	}
	else { return false; }
}
void Tile::Detach()
{
	attachment.reset();
}
	
void Tile::Render( float x, float y )
{
	spr->Render( (int)x, (int)y );
}
