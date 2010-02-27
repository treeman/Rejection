#include "MovingObject.hpp"

MovingObject::MovingObject()
{
	wants_stop = stop_set = false;
	is_paused = false;
	DirFaceDown();
	last_move.Start();
}

Tree::Rect MovingObject::Bounds() const
{
	return Tree::Rect( pos.x + 1, pos.y + 1, 30, 30 );
}

void MovingObject::StopAt( Vec2D target )
{
	stop_pos = target;
	stop_set = true;
}
void MovingObject::MoveStop()
{
	wants_stop = true;
	last_move.Restart();
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
	last_move.Restart();
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
	last_move.Restart();
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
	last_move.Restart();
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
	last_move.Restart();
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
