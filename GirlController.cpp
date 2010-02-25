#include "GirlController.hpp"
#include "Girl.hpp"

GirlController::GirlController()
{
	
}

void GirlController::Attach( boost::shared_ptr<Girl> girl )
{
	girls.push_back( girl );
}
void GirlController::Detach( boost::shared_ptr<Girl> girl )
{
	std::remove( girls.begin(), girls.end(), girl );
}

void GirlController::Update( float dt )
{
	for( Girls::iterator it = girls.begin(); it != girls.end(); ++it ) {
		UpdateGirl( *it, dt );
	}
}
void GirlController::UpdateGirl( boost::shared_ptr<Girl> girl, float )
{
	const Girl::Vision vision = girl->GetVision();
	
//	GridPos pos;
//	
//	for( int x = 0; x < vision.size(); ++x ) {
//		for( int y = 0; y < vision[x].size(); ++y ) {
//			if( vision[x][y] == VISION_SELF ) {
//				pos.x = x; pos.y = y;
//			}
//		}
//	}
	
	
}
