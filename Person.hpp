#pragma once

#include "MovingObject.hpp"

class Person : public MovingObject {
public:
	virtual ~Person() { }
	
	virtual void Update( float dt ) = 0;
	virtual void Render() = 0;
};
