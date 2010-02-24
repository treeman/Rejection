#pragma once

#include "Tree/Vec2D.hpp"

class MovingObject {
public:
	virtual ~MovingObject() { }
	
	void SetPos( Vec2D p ) { pos = p; }
	Vec2D GetPos() const { return pos; }
	
	void MoveTo( Vec2D p ) { target = p; }
	Vec2D GetTarget() const { return target; }
	
	void SetVel( Vec2D v ) { vel = v; }
	Vec2D GetVel() const { return vel; }
	
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	
	bool WantsLeft();
	bool WantsRight();
	bool WantsUp();
	bool WantsDown();
	
	bool FacesLeft();
	bool FacesRight();
	bool FacesUp();
	bool FacesDown();
	
	void UpdateMovement();
protected:
	Vec2D pos;
	Vec2D target;
	
	Vec2D vel;
};
