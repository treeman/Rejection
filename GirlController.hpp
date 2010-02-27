#pragma once

#include "Controller.hpp"
#include "Grid.hpp"
#include "Person.hpp"
#include "Tree/Timer.hpp"

class Girl;

class GirlController : public Controller {
public:
	GirlController();
	
	void Attach( boost::shared_ptr<Girl> girl );
	void Detach( boost::shared_ptr<Girl> girl );
	
	void Update( float dt );
private:
	void UpdateGirl( boost::shared_ptr<Girl> girl, float dt );

	typedef std::vector<boost::shared_ptr<Girl> > Girls;
	Girls girls;
	
	bool IsValid( int x, int y, Person::Vision vision );
	bool IsDudeVisible( GridPos &pos, Person::Vision vision );
	bool IsClearPath( Vec2D &dir, boost::shared_ptr<Girl> girl );
	bool IsFree( int x, int y, Person::Vision vision );
	Vec2D RandomDir( Person::Vision vision );
	
	//hilarious
	//but necessery to avoid a lot of "is girl already moving right?"
	//questions
	void MoveStop( boost::shared_ptr<Girl> girl );
	void MoveLeft( boost::shared_ptr<Girl> girl );
	void MoveRight( boost::shared_ptr<Girl> girl );
	void MoveUp( boost::shared_ptr<Girl> girl );
	void MoveDown( boost::shared_ptr<Girl> girl );
	
	HgeObj hge;
	
	Tree::Timer print_vision_t;
};
