#include "GrassTiles.hpp"
#include "Tree/Log.hpp"
#include "Tweaks.hpp"

GrassTile::GrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader ) : Tile( pos, spr_loader )
{
	timer = TWEAKS->GetFloat( "grass_lvl3_grow_time" );
	walk_eff.Load( "sound/footstep_grass.wav" );
}

void GrassTile::Reset()
{
	timer = TWEAKS->GetFloat( "grass_lvl3_grow_time" );
}

void GrassTile::WalkOver()
{
	timer = 0;
	if( attachment ) attachment->WalkOver();
}
bool GrassTile::IsSeeThrough()
{
	if( attachment && attachment->IsSeeThrough() ) return true;
	else return timer <= TWEAKS->GetFloat( "grass_lvl3_grow_time" );
}
bool GrassTile::IsWalkable()
{
	if( attachment ) return attachment->IsWalkable();
	else return true;
}

void GrassTile::Update( float dt )
{
	timer += dt;
	
	if( attachment ) timer = 0;
	
	const float lvl2 = TWEAKS->GetFloat( "grass_lvl2_grow_time" );
	const float lvl3 = TWEAKS->GetFloat( "grass_lvl3_grow_time" );
	
	if( timer <= lvl2 ) { 
		if( curr_spr != lvl1_spr ) PlayWalk();
		curr_spr = lvl1_spr;
	}
	else if( timer <= lvl3 ) { curr_spr = lvl2_spr; }
	else { curr_spr = lvl3_spr; }
}

void GrassTile::Render()
{
	if( curr_spr ) curr_spr->spr->Render( (int)pos.x, (int)pos.y );
	if( attachment) attachment->Render();
}

void GrassTile::PlayWalk()
{
	hge->Effect_PlayEx( walk_eff, 70 );
}

DarkGrassTile::DarkGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader ) : GrassTile( pos, spr_loader )
{
	lvl1_spr = spr_loader->Get( "darkgrass_lvl1" );
	lvl2_spr = spr_loader->Get( "darkgrass_lvl2" );
	lvl3_spr = spr_loader->Get( "darkgrass_lvl3" );
	curr_spr = lvl3_spr;
	is_dark = true;
}

LightGrassTile::LightGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader ) : GrassTile( pos, spr_loader )
{
	lvl1_spr = spr_loader->Get( "lightgrass_lvl1" );
	lvl2_spr = spr_loader->Get( "lightgrass_lvl2" );
	lvl3_spr = spr_loader->Get( "lightgrass_lvl3" );
	curr_spr = lvl3_spr;
	is_dark = false;
}

GeekDarkGrassTile::GeekDarkGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader ) : GrassTile( pos, spr_loader )
{
	lvl1_spr = spr_loader->Get( "geekdarkgrass_lvl1" );
	lvl2_spr = spr_loader->Get( "geekdarkgrass_lvl2" );
	lvl3_spr = spr_loader->Get( "geekdarkgrass_lvl3" );
	curr_spr = lvl3_spr;
	is_dark = true;
}

GeekLightGrassTile::GeekLightGrassTile( Vec2D pos, boost::shared_ptr<SpriteLoader> spr_loader ) : GrassTile( pos, spr_loader )
{
	lvl1_spr = spr_loader->Get( "geeklightgrass_lvl1" );
	lvl2_spr = spr_loader->Get( "geeklightgrass_lvl2" );
	lvl3_spr = spr_loader->Get( "geeklightgrass_lvl3" );
	curr_spr = lvl3_spr;
	is_dark = false;
}
