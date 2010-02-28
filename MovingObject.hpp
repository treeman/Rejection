#pragma once

#include "Tree/Vec2D.hpp"
#include "Tree/Rect.hpp"
#include "Tree/Timer.hpp"

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
	
	void PushLeft( float power );
	void PushRight( float power );
	void PushUp( float power );
	void PushDown( float power );
	
	bool IsMoving();
	
	bool WantsStop();
	
	bool WantsLeft();
	bool WantsRight();
	bool WantsUp();
	bool WantsDown();
	
	float LastMove();
	
	void Pause( float time );
	void Unpause();
	bool IsPaused();
	
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
	
	Tree::Timer last_move;
	
	virtual void GetPaused() { }
	virtual void GetUnpaused() { }
	
	bool is_paused;
	Tree::Timer pause_timer;
	float pause_time;
	
	void AMove();
	
	float push_power;
	Vec2D push_dir;
};
