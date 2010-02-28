#pragma once

#include "TileObject.hpp"

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
	virtual ~Trap() { }
	
	int GetCost();
	
	void SetInfo( TrapInfo i ) { info = i; }
	TrapInfo GetInfo() { return info; }
protected:
	TrapInfo info;
};
