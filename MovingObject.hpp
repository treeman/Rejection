#pragma once

#include "Tree/Vec2D.hpp"
#include "Tree/Rect.hpp"

class MovingObject {
public:
	MovingObject();
	virtual ~MovingObject() { }
	
	virtual Tree::Rect Bounds() const;
	
	void SetPos( Vec2D p ) { pos = p; }
	void SetXPos( float x ) { pos.x = x; }
	void SetYPos( float y ) { pos.y = y; }
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
	
	void MoveOneLeft();
	void MoveOneRight();
	void MoveOneUp();
	void MoveOneDown();
	
	bool IsMoving();
	
	bool WantsStop();
	bool WantsStopNext();
	
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
	bool wants_stop_next;
	bool stop_set;
	Vec2D stop_pos;

	void DirFaceLeft();
	void DirFaceRight();
	void DirFaceUp();
	void DirFaceDown();
	
	void ForceStop();
	
	void ClearNext();
	void NextLeft();
	void NextRight();
	void NextUp();
	void NextDown();
	
	Vec2D next_move;
	Vec2D face_dir;
};
