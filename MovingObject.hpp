#pragma once

#include "Tree/Vec2D.hpp"

class MovingObject {
public:
	MovingObject();
	virtual ~MovingObject() { }
	
	void SetPos( Vec2D p ) { pos = p; }
	Vec2D GetPos() const { return pos; }
	
	void SetVel( Vec2D v ) { vel = v; }
	void SetXVel( float xv ) { vel.x = xv; }
	void SetYVel( float yv ) { vel.y = yv; }
	Vec2D GetVel() const { return vel; }
	
	void StopAt( Vec2D stop_pos );
	
	void MoveStop();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	
	bool WantsStop();
	bool WantsLeft();
	bool WantsRight();
	bool WantsUp();
	bool WantsDown();
	
	virtual void FaceLeft() { }
	virtual void FaceRight() { }
	virtual void FaceUp() { }
	virtual void FaceDown() { }
	
	virtual float GetSpeed() = 0;
	
	bool FacesLeft();
	bool FacesRight();
	bool FacesUp();
	bool FacesDown();
	
	void UpdateMovement( float dt );
protected:
	Vec2D pos;
	Vec2D vel;
	
	bool wants_stop;
	bool stop_set;
	Vec2D stop_pos;
private:
	void DirFaceLeft();
	void DirFaceRight();
	void DirFaceUp();
	void DirFaceDown();
	
	void ForceStop();
	
	Vec2D face_dir;
};
