#include "Person.hpp"

Person::Person()
{
	const int vision_size = 5;
	
	vision.resize( vision_size );
	for( int n = 0; n < vision_size; ++n ) {
		vision[n].resize( vision_size, VISION_OBSUCRED );
	}
	vision[vision_size / 2][vision_size / 2] = VISION_SELF;
}

void Person::SetVision( Vision v ) 
{ 
	vision = v; 
}
Person::Vision Person::GetVision() { return vision; }
