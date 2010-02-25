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
	
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	debug_dude.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "dude_debug", boost::weak_ptr<Tree::BaseDator>( debug_dude ) );
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
	
	if( debug_dude->Val() )
	{
		std::string face;
		if( Vec2D::left == face_dir ) face = "left";
		else if( Vec2D::right == face_dir ) face = "right ";
		else if( Vec2D::up == face_dir ) face = "up";
		else if( Vec2D::down == face_dir ) face = "down";
		
		fnt->printf( 140, 5, HGETEXT_LEFT, "dude: p:%.0f,%.0f v:%.0f,%.0f stop:%i stop_set:%i stop_pos:%.0f,%.0f face:%s",
			pos.x, pos.y, vel.x, vel.y, wants_stop, stop_set, stop_pos.x, stop_pos.y, face.c_str() );
	}
}
