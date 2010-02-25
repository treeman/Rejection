#include "Dude.hpp"

Dude::Dude( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr_loader->Load( "sprites.lua" );
	
	curr_spr = spr_loader->Get( "dude_left" );
	spr_map[ "dude_left" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_right" );
	spr_map[ "dude_right" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_back" );
	spr_map[ "dude_back" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_front" );
	spr_map[ "dude_front" ] = curr_spr;
}

Tree::Rect Dude::Bounds() const
{
	return Tree::Rect( pos.x + 1, pos.y + 1, 30, 30 );
}

float Dude::GetSpeed()
{
	return 100;
}

void Dude::Update( float dt )
{
	UpdateMovement( dt );
}
void Dude::Render()
{
	curr_spr->spr->Render( (int)pos.x, (int)pos.y );
}
