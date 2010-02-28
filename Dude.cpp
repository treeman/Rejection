#include "Dude.hpp"
#include "Tweaks.hpp"

Dude::Dude( boost::shared_ptr<SpriteLoader> spr_loader )
{
	curr_spr = spr_loader->Get( "dude_left" );
	spr_map[ "dude_left" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_right" );
	spr_map[ "dude_right" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_back" );
	spr_map[ "dude_back" ] = curr_spr;
	curr_spr = spr_loader->Get( "dude_front" );
	spr_map[ "dude_front" ] = curr_spr;
	
	wants_action = false;
	
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	debug_dude.reset( new Tree::Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "dude_debug", boost::weak_ptr<Tree::BaseDator>( debug_dude ) );
}

float Dude::GetSpeed()
{
	return TWEAKS->GetFloat( "dude_speed" );
}

void Dude::FaceLeft()
{
	curr_spr = spr_map["dude_left"];
}
void Dude::FaceRight()
{
	curr_spr = spr_map["dude_right"];
}
void Dude::FaceUp()
{
	curr_spr = spr_map["dude_back"];
}
void Dude::FaceDown()
{
	curr_spr = spr_map["dude_front"];
}

bool Dude::WantsAction()
{
	return wants_action && !IsMoving();
}
void Dude::DoAction()
{
	if( !IsMoving() ) wants_action = true;
}
void Dude::CancelAction()
{
	wants_action = false;
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
		
		fnt->printf( 140, 5, HGETEXT_LEFT, "dude: p:%.0f,%.0f v:%.0f,%.0f stop:%i stop_set:%i stop_pos:%.0f,%.0f face:%s l:%i r%i u%i d%i",
			pos.x, pos.y, vel.x, vel.y, wants_stop, stop_set, stop_pos.x, stop_pos.y, face.c_str(),
			WantsLeft(), WantsRight(), WantsUp(), WantsDown()
		);
	}
}
