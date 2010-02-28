#include "MovingObject.hpp"

MovingObject::MovingObject()
{
	wants_stop = stop_set = false;
	is_paused = false;
	DirFaceDown();
	last_move.Start();
	push_power = 0;
}

Tree::Rect MovingObject::Bounds() const
{
	return Tree::Rect( pos.x, pos.y, 32, 32 );
}

void MovingObject::StopAt( Vec2D target )
{
	stop_pos = target;
	stop_set = true;
}
void MovingObject::MoveStop()
{
	wants_stop = true;
	AMove();
}
void MovingObject::MoveLeft()
{
	if( !IsMoving() ) {
		vel.x = -GetSpeed(); vel.y = 0;
		DirFaceLeft();
		wants_stop = false;
	}
	else {
		NextLeft();
	}
	AMove();
}
void MovingObject::MoveRight()
{
	if( !IsMoving() ) {
		vel.x = GetSpeed(); vel.y = 0;
		DirFaceRight();
		wants_stop = false;
	}
	else {
		NextRight();
	}
	AMove();
}
void MovingObject::MoveUp()
{
	if( !IsMoving() ) {
		vel.x = 0; vel.y = -GetSpeed();
		DirFaceUp();
		wants_stop = false;
	}
	else {
		NextUp();
	}
	AMove();
}
void MovingObject::MoveDown()
{
	if( !IsMoving() ) {
		vel.x = 0; vel.y = GetSpeed();
		DirFaceDown();
		wants_stop = false;
	}
	else {
		NextDown();
	}
	AMove();
}
void MovingObject::PushLeft( float power )
{
	if( power > push_power ) {
		push_power = power;
		push_dir = Vec2D::left;
	}
}
void MovingObject::PushRight( float power )
{
	if( power > push_power ) {
		push_power = power;
		push_dir = Vec2D::right;
	}
}
void MovingObject::PushUp( float power )
{
	if( power > push_power ) {
		push_power = power;
		push_dir = Vec2D::up;
	}
}
void MovingObject::PushDown( float power )
{
	if( power > push_power ) {
		push_power = power;
		push_dir = Vec2D::down;
	}
}
bool MovingObject::IsMoving()
{
	return vel.x != 0 || vel.y != 0;
}
bool MovingObject::WantsStop()
{
	return wants_stop && !stop_set;
}
bool MovingObject::WantsLeft()
{
	return vel.x < 0;
}
bool MovingObject::WantsRight()
{
	return vel.x > 0;
}
bool MovingObject::WantsUp()
{
	return vel.y < 0;
}
bool MovingObject::WantsDown()
{
	return vel.y > 0;
}

float MovingObject::LastMove()
{
	return last_move.GetTime();
}

void MovingObject::Pause( float time )
{
	is_paused = true;
	pause_time = time;
	pause_timer.Restart();
	GetPaused();
}
void MovingObject::Unpause()
{
	is_paused = false;
	GetUnpaused();
}
bool MovingObject::IsPaused()
{
	return is_paused;
}

bool MovingObject::FacesLeft()
{
	return Vec2D::left == face_dir;
}
bool MovingObject::FacesRight()
{
	return Vec2D::right == face_dir;
}
bool MovingObject::FacesUp()
{
	return Vec2D::up == face_dir;
}
bool MovingObject::FacesDown()
{
	return Vec2D::down == face_dir;
}

void MovingObject::UpdateMovement( float dt )
{
	if( push_power > 0 ) {
		MoveStop();
		if( push_dir == Vec2D::left ) MoveLeft();
		if( push_dir == Vec2D::right ) MoveRight();
		if( push_dir == Vec2D::up ) MoveUp();
		if( push_dir == Vec2D::down ) MoveDown();
	}
	push_power = 0;
	
	pos += vel * dt;
	if( is_paused && pause_timer.GetTime() > pause_time ) {
		Unpause();
	}
	if( wants_stop && stop_set ) {
		if( WantsLeft() && pos.x < stop_pos.x ) {
			ForceStop();
		}
		else if( WantsRight() && pos.x > stop_pos.x ) {
			ForceStop();
		}
		else if( WantsUp() && pos.y < stop_pos.y ) {
			ForceStop();
		}
		else if( WantsDown() && pos.y > stop_pos.y ) {
			ForceStop();
		}
	}
}

void MovingObject::DirFaceLeft()
{
	FaceLeft();
	face_dir = Vec2D::left;
}
void MovingObject::DirFaceRight()
{
	FaceRight();
	face_dir = Vec2D::right;
}
void MovingObject::DirFaceUp()
{
	FaceUp();
	face_dir = Vec2D::up;
}
void MovingObject::DirFaceDown()
{
	FaceDown();
	face_dir = Vec2D::down;
}

void MovingObject::ForceStop()
{
	wants_stop = stop_set = false;
	pos = stop_pos;
	vel = Vec2D::zero;
	if( next_move != Vec2D::zero ) {
		if( next_move == Vec2D::left ) MoveLeft();
		if( next_move == Vec2D::right ) MoveRight();
		if( next_move == Vec2D::up ) MoveUp();
		if( next_move == Vec2D::down ) MoveDown();
		ClearNext();
	}
}

void MovingObject::ClearNext()
{
	next_move = Vec2D::zero;
}
void MovingObject::NextLeft()
{
	next_move = Vec2D::left;
	MoveStop();
}
void MovingObject::NextRight()
{
	next_move = Vec2D::right;
	MoveStop();
}
void MovingObject::NextUp()
{
	next_move = Vec2D::up;
	MoveStop();
}
void MovingObject::NextDown()
{
	next_move = Vec2D::down;
	MoveStop();
}

void MovingObject::AMove()
{
	last_move.Restart();
}
