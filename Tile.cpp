#include "Tile.hpp"

Tile::Tile( Vec2D p ) : pos( p )
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

Tree::Rect Tile::Bounds() const 
{ 
	return Tree::Rect( pos.x, pos.y, 32, 32 );
}
