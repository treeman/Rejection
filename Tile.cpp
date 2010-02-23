#include "Tile.hpp"

Tile::Tile()
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
