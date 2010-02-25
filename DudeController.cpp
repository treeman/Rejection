#include "DudeController.hpp"
#include "Dude.hpp"

DudeController::DudeController( boost::shared_ptr<Dude> d ) : dude( d )
{
	
}
	
bool DudeController::HandleEvent( hgeInputEvent &e )
{
	if( e.type == INPUT_KEYDOWN ) {
		switch( e.key ) {
			case HGEK_LEFT:
				dude->MoveLeft();
				break;
			case HGEK_RIGHT:
				dude->MoveRight();
				break;
			case HGEK_UP:
				dude->MoveUp();
				break;
			case HGEK_DOWN:
				dude->MoveDown();
				break;
		}
	}
}
void DudeController::Update( float dt )
{
	
}
