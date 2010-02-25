#include "Girl.hpp"

Girl::Girl( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr_loader->Load( "sprites.lua" );
	
	curr_spr = spr_loader->Get( "girl_front" );
	spr_map[ "girl_front" ] = curr_spr;
	
	const int vision_size = 5;
	
	vision.resize( vision_size );
	for( int n = 0; n < vision_size; ++n ) {
		vision[n].resize( vision_size, VISION_FREE );
	}
	vision[vision_size / 2][vision_size / 2] = VISION_SELF;
	
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	debug_girl.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "girl_debug", boost::weak_ptr<Tree::BaseDator>( debug_girl ) );
}

float Girl::GetSpeed()
{
	return 100;
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
