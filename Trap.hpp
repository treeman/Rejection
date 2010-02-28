#pragma once

#include "TileObject.hpp"
#include "Tree/Vec2D.hpp"

struct TrapInfo {
	TrapInfo() { Reset(); }
	TrapInfo( std::string _name, int _cost ) : name( _name ), cost( _cost )
	{ }
	void Reset() {
		name = "";
		cost = 0;
	}
	std::string name;
	int cost;
};

class Trap : public TileObject {
public:
	Trap();
	virtual ~Trap() { }
	
	void FaceLeft();
	void FaceRight();
	void FaceUp();
	void FaceDown();
	
	int GetActivationRadius() { return 0; }
	
	virtual void Activate() { is_active = true; }
	virtual void Deactivate() { is_active = false; }
	
	virtual bool IsActive() { return is_active; }
	
	void SetInfo( TrapInfo i ) { info = i; }
	TrapInfo GetInfo() { return info; }
protected:
	TrapInfo info;
	Vec2D dir;
};
