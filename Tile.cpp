#include "Tile.hpp"

Tile::Tile( Vec2D p ) : pos( p )
{
	
}

boost::shared_ptr<TileObject> Tile::Attachment()
{
	return attachment;
}

bool Tile::Attach( boost::shared_ptr<TileObject> a )
{
//	if( !attachment ) { return false; }
//	else {
		attachment = a;
		attachment->SetPos( pos );
		return true;
//	}
}
void Tile::Detach()
{
	attachment.reset();
}
bool Tile::IsWalkable()
{
	if( attachment ) return attachment->IsWalkable();
	else return true;
}
bool Tile::IsSeeThrough()
{
	if( attachment ) return attachment->IsSeeThrough();
	else return true;
}

Tree::Rect Tile::Bounds() const 
{ 
	return Tree::Rect( pos.x, pos.y, 32, 32 );
}
