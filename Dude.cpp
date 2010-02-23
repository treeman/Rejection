#include "Dude.hpp"

Dude::Dude() : spr_loader( new SpriteLoader() )
{
	spr_loader->Load( "dude.lua" );
	
	curr_spr = spr_loader->Get( "dude_left" );
	spr_map[ "dude_left" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_right" );
	spr_map[ "dude_right" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_back" );
	spr_map[ "dude_back" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_front" );
	spr_map[ "dude_front" ] = curr_spr;
}

void Dude::Update( float dt )
{
	
}
void Dude::Render()
{
	curr_spr->spr->Render( 320, 320 );
}
