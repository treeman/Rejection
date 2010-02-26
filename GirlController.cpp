#include "GirlController.hpp"
#include "Girl.hpp"
#include "Tree/Log.hpp"

GirlController::GirlController()
{
	print_vision_t.Start();
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
//	if( girl->IsMoving() ) return;
	
	const Person::Vision vision = girl->GetVision();
	
	GridPos pos( vision.size() / 2, vision[0].size() / 2 );
	
	//kill the spambot!! :@
	if( print_vision_t.GetTime() > 1.0 ) {
		//print a nice debug view of the girls vision
		std::string vision_string = "girl vision:\n";
		for( int y = 0; y < vision.size(); ++y ) {
			for( int x = 0; x < vision[y].size(); ++x ) {
				switch( vision[x][y] ) {
					case VISION_FREE: vision_string += "."; break;
					case VISION_OBSUCRED: vision_string += "x"; break;
					case VISION_DUDE: vision_string += "D"; break;
					case VISION_SELF: vision_string += "g"; break;
					case VISION_INVALID: vision_string += "i"; break;
				}
			}
			vision_string += "\n";
		}
		L_ << vision_string;
		print_vision_t.Restart();
	}
	
	if( girl->FacesLeft() && pos.x > 0 &&  
		( vision[pos.x-1][pos.y] == VISION_DUDE || vision[pos.x-1][pos.y] == VISION_FREE ) )
	{
//		L_ << "moving left";
		girl->MoveLeft();
	}
	else if( girl->FacesRight() && pos.x < vision.size() - 1 &&  
		( vision[pos.x+1][pos.y] == VISION_DUDE || vision[pos.x+1][pos.y] == VISION_FREE ) )
	{
//		L_ << "moving right";
		girl->MoveRight();
	}
	else if( girl->FacesUp() && pos.y > 0 &&  
		( vision[pos.x][pos.y-1] == VISION_DUDE || vision[pos.x][pos.y-1] == VISION_FREE ) )
	{
//		L_ << "moving up";
		girl->MoveUp();
	}
	else if( girl->FacesDown() && pos.y < vision[pos.x].size() - 1 &&  
		( vision[pos.x][pos.y+1] == VISION_DUDE || vision[pos.x][pos.y+1] == VISION_FREE ) )
	{
//		L_ << "moving down";
		if( !girl->IsMoving() ) girl->MoveDown();
	}
}

void GirlController::IsValid( int x, int y, Person::Vision vision )
{
	
}
