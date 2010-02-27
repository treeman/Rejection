#include "Girl.hpp"
#include "Tweaks.hpp"

Girl::Girl( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr_loader->Load( "sprites.lua" );
	
	curr_spr = spr_loader->Get( "girl_front" );
	spr_map[ "girl_front" ] = curr_spr;
	
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	debug_girl.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "girl_debug", boost::weak_ptr<Tree::BaseDator>( debug_girl ) );
}

float Girl::GetSpeed()
{
	return TWEAKS->GetFloat( "girl_speed" );
}

void Girl::FaceLeft()
{
//	curr_spr = spr_map["dude_left"];
}
void Girl::FaceRight()
{
//	curr_spr = spr_map["dude_right"];
}
void Girl::FaceUp()
{
//	curr_spr = spr_map["dude_back"];
}
void Girl::FaceDown()
{
//	curr_spr = spr_map["dude_front"];
}

void Girl::Update( float dt )
{
	UpdateMovement( dt );
}
void Girl::Render()
{
	curr_spr->spr->Render( (int)pos.x, (int)pos.y );
}
