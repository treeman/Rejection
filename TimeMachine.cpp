#include "TimeMachine.hpp"

TimeMachine::TimeMachine( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr = spr_loader->Get( "timemachine" );
}

void TimeMachine::Update( float dt )
{
	
}
void TimeMachine::Render()
{
	spr->spr->Render( pos.x, pos.y );
}
