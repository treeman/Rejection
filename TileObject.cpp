#include "TileObject.hpp"

Tree::Rect TileObject::Bounds() const
{
	return Tree::Rect( pos.x + 1, pos.y + 1, 30, 30 );
}
