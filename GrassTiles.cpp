#include "GrassTiles.hpp"

GrassTile::GrassTile()
{
	timer = 0;
}

void GrassTile::Update( float dt )
{
	timer += dt;
	
	if( timer <= 2.0 ) { curr_spr = lvl1_spr; }
	else if( timer <= 5.0 ) { curr_spr = lvl2_spr; }
	else { curr_spr = lvl3_spr; }
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
	curr_spr = lvl1_spr;
}

LightGrassTile::LightGrassTile( boost::shared_ptr<SpriteLoader> spr_loader )
{
	lvl1_spr = spr_loader->Get( "lightgrass_lvl1" );
	lvl2_spr = spr_loader->Get( "lightgrass_lvl2" );
	lvl3_spr = spr_loader->Get( "lightgrass_lvl3" );
	curr_spr = lvl1_spr;
}
