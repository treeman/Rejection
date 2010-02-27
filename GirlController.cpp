#include "GirlController.hpp"
#include "Girl.hpp"
#include "Tree/Log.hpp"
#include "Tree/Util.hpp"
#include "Tree/Math.hpp"

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
	const Person::Vision vision = girl->GetVision();
	
	GridPos my_pos( vision.size() / 2, vision[0].size() / 2 );
	
//	//kill the spambot!! :@
//	if( print_vision_t.GetTime() > 2.0 ) {
//		//print a nice debug view of the girls vision
//		std::string vision_string = "girl vision:\n";
//		for( int y = 0; y < vision.size(); ++y ) {
//			for( int x = 0; x < vision[y].size(); ++x ) {
//				switch( vision[x][y] ) {
//					case VISION_FREE: vision_string += "."; break;
//					case VISION_OBSUCRED: vision_string += "x"; break;
//					case VISION_DUDE: vision_string += "D"; break;
//					case VISION_SELF: vision_string += "g"; break;
//					case VISION_INVALID: vision_string += "i"; break;
//				}
//			}
//			vision_string += "\n";
//		}
//		L_ << vision_string;
//		print_vision_t.Restart();
//	}
	
	//first check if we see the dude
	GridPos dude_pos;
	if( IsDudeVisible( dude_pos, vision ) ) {
		if( dude_pos.x < my_pos.x ) MoveLeft( girl );
		else if( dude_pos.x > my_pos.x ) MoveRight( girl );
		else if( dude_pos.y < my_pos.y ) MoveUp( girl );
		else if( dude_pos.y > my_pos.y ) MoveDown( girl );
		return;
	}
	
	//then try to follow a clear path
	//this doesn't include the back path
	Vec2D clear_path;
	if( girl->LastMove() > 0.3 && IsClearPath( clear_path, girl ) ) {
		if( clear_path == Vec2D::left ) MoveLeft( girl );
		else if( clear_path == Vec2D::right ) MoveRight( girl );
		else if( clear_path == Vec2D::up ) MoveUp( girl );
		else if( clear_path == Vec2D::down ) MoveDown( girl );
		return;
	}
	
	//if we see nothing choose a random direction
	if( !girl->IsMoving() && girl->LastMove() > 1.0 ) {
		Vec2D dir = RandomDir( vision );
		if( dir == Vec2D::left ) MoveLeft( girl );
		else if( dir == Vec2D::right ) MoveRight( girl );
		else if( dir == Vec2D::up ) MoveUp( girl );
		else if( dir == Vec2D::down ) MoveDown( girl );
	}
	
	//if we havn't had a move for a while
	//stop so she can think ^^
	if( girl->LastMove() > 1.5 ) {
		MoveStop( girl );
	}
}

bool GirlController::IsValid( int x, int y, Person::Vision vision )
{
	return x >= 0 && x < vision.size() && y >= 0 && y < vision[x].size();
}
bool GirlController::IsDudeVisible( GridPos &pos, Person::Vision vision )
{
	const GridPos my_pos( vision.size() / 2, vision[0].size() / 2 );
	
	for( int x = 0; x < vision.size(); ++x ) {
		if( vision[x][my_pos.y] == VISION_DUDE ) {
			pos.x = x; pos.y = my_pos.y;
			return true;
		}
	}
	for( int y = 0; y < vision[my_pos.x].size(); ++y ) {
		if( vision[my_pos.x][y] == VISION_DUDE ) {
			pos.x = my_pos.x; pos.y = y;
			return true;
		}
	}
	return false;
}

bool GirlController::IsClearPath( Vec2D &dir, boost::shared_ptr<Girl> girl )
{
	const Person::Vision vision = girl->GetVision();
	const GridPos my_pos( vision.size() / 2, vision[0].size() / 2 );
	
	Vec2D face_dir;
	if( girl->FacesLeft() ) face_dir = Vec2D::left;
	else if( girl->FacesRight() ) face_dir = Vec2D::right;
	else if( girl->FacesUp() ) face_dir = Vec2D::up;
	else if( girl->FacesDown() ) face_dir = Vec2D::down;
	
	typedef std::vector<Vec2D> FreePaths;
	FreePaths free_paths;
	
	//she's facing left or right
	if( face_dir.x != 0 ) {
		//meaning we'll check both up and down
		if( IsFree( my_pos.x, my_pos.y - 1, vision ) ) {
			free_paths.push_back( Vec2D::up );
		}
		if( IsFree( my_pos.x, my_pos.y + 1, vision ) ) {
			free_paths.push_back( Vec2D::down );
		}
		//and check the dir she's facing
		if( IsFree( my_pos.x + face_dir.x, my_pos.y, vision ) ) {
			free_paths.push_back( face_dir );
		}
	}
	//she's facing up or down
	else {
		//left and right
		if( IsFree( my_pos.x - 1, my_pos.y, vision ) ) {
			free_paths.push_back( Vec2D::left );
		}
		if( IsFree( my_pos.x + 1, my_pos.y, vision ) ) {
			free_paths.push_back( Vec2D::right );
		}
		//and check the dir she's facing
		if( IsFree( my_pos.x, my_pos.y + face_dir.y, vision ) ) {
			free_paths.push_back( face_dir );
		}
	}
	if( !free_paths.empty() ) {
//		for( FreePaths::iterator it = free_paths.begin(); it != free_paths.end(); ++it ) {
//			L_ << "path: " << it->x << "," << it->y;
//		}
		
		dir = *Tree::random( free_paths.begin(), free_paths.end() );
		return true;
	}
	else {
		return false;
	}
}
bool GirlController::IsFree( int x, int y, Person::Vision vision )
{
	if( !IsValid( x, y, vision ) ) return false;
	else return vision[x][y] == VISION_FREE;
}
Vec2D GirlController::RandomDir( Person::Vision vision )
{
	const GridPos my_pos( vision.size() / 2, vision[0].size() / 2 );
	
	typedef std::vector<Vec2D> FreePaths;
	FreePaths free_paths;
	
	if( IsValid( my_pos.x - 1, my_pos.y, vision ) ) free_paths.push_back( Vec2D::left );
	if( IsValid( my_pos.x + 1, my_pos.y, vision ) ) free_paths.push_back( Vec2D::right );
	if( IsValid( my_pos.x, my_pos.y - 1, vision ) ) free_paths.push_back( Vec2D::up );
	if( IsValid( my_pos.x, my_pos.y + 1, vision ) ) free_paths.push_back( Vec2D::down );
	
	if( !free_paths.empty() ) {
		return *Tree::random( free_paths.begin(), free_paths.end() );
	}
	else {
		return Vec2D::zero;
	}
}

void GirlController::MoveStop( boost::shared_ptr<Girl> girl )
{
	if( girl->IsMoving() ) girl->MoveStop();
}
void GirlController::MoveLeft( boost::shared_ptr<Girl> girl )
{
	if( !girl->WantsLeft() ) girl->MoveLeft();
}
void GirlController::MoveRight( boost::shared_ptr<Girl> girl )
{
	if( !girl->WantsRight() ) girl->MoveRight();
}
void GirlController::MoveUp( boost::shared_ptr<Girl> girl )
{
	if( !girl->WantsUp() ) girl->MoveUp();
}
void GirlController::MoveDown( boost::shared_ptr<Girl> girl )
{
	if( !girl->WantsDown() ) girl->MoveDown();
}
