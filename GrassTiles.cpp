#include "GrassTiles.hpp"

GrassTile::GrassTile()
{
	timer = 0;
}

void GrassTile::Update( float dt )
{
	timer += dt;
}

void GrassTile::Render( float x, float y )
{
	if( curr_spr ) curr_spr->spr->Render( (int)x, (int)y );
}

DarkGrassTile::DarkGrassTile( boost::shared_ptr<SpriteLoader> spr_loader )
{
	lvl1_spr = spr_loader->Get( "darkgrass_lvl1" );
	lvl2_spr = spr_loader->Get( "darkgrass_lvl2" );
	lvl3_spr = spr_loader->Get( "darkgrass_lvl3" );
}

LightGrassTile::LightGrassTile( boost::shared_ptr<SpriteLoader> spr_loader )
{
	lvl1_spr = spr_loader->Get( "lightgrass_lvl1" );
	lvl2_spr = spr_loader->Get( "lightgrass_lvl2" );
	lvl3_spr = spr_loader->Get( "lightgrass_lvl3" );
}
