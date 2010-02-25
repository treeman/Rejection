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
void GirlController::UpdateGirl( boost::shared_ptr<Girl> girl, float dt )
{
	Girl::Vision vision = girl->GetVision();
}
