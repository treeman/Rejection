#include "Traps.hpp"

BlowerTrap::BlowerTrap( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr = spr_loader->Get( "blower_trap" );
}
void BlowerTrap::Render()
{
	spr->spr->Render( pos.x, pos.y );
}

MagnetTrap::MagnetTrap( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr = spr_loader->Get( "magnet_trap" );
}

void MagnetTrap::Render()
{
	spr->spr->Render( pos.x, pos.y );
}
