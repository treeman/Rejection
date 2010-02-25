#include "MovingObject.hpp"

MovingObject::MovingObject()
{
	wants_stop = stop_set = false;
}
void MovingObject::StopAt( Vec2D target )
{
	stop_pos = target;
	stop_set = true;
}
void MovingObject::MoveStop()
{
	wants_stop = true;
}
void MovingObject::MoveLeft()
{
	vel.x = -GetSpeed(); vel.y = 0;
	DirFaceLeft();
}
void MovingObject::MoveRight()
{
	vel.x = GetSpeed(); vel.y = 0;
	DirFaceRight();
}
void MovingObject::MoveUp()
{
	vel.x = 0; vel.y = -GetSpeed();
	DirFaceUp();
}
void MovingObject::MoveDown()
{
	vel.x = 0; vel.y = GetSpeed();
	DirFaceDown();
}
bool MovingObject::WantsStop()
{
	return wants_stop;
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
	if( stop_set ) {
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
}
