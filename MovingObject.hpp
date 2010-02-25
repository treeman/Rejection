#pragma once

#include "Tree/Vec2D.hpp"

class MovingObject {
public:
	virtual ~MovingObject() { }
	
	void SetPos( Vec2D p ) { pos = p; }
	Vec2D GetPos() const { return pos; }
	
	void SetVel( Vec2D v ) { vel = v; }
	Vec2D GetVel() const { return vel; }
	
	void Stop();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	
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
private:
	void DirFaceLeft();
	void DirFaceRight();
	void DirFaceUp();
	void DirFaceDown();
	
	Vec2D face_dir;
};
