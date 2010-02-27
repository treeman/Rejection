#pragma once

class WorldListener {
public:
	virtual ~WorldListener() { }
	
	virtual void SetLife( int life ) { }
	virtual void SetMoney( int money ) { }
};
