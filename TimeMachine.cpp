#include "TimeMachine.hpp"

TimeMachine::TimeMachine( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr = spr_loader->Get( "time_machine" );
	//just a white area as big as the "boxes" in the time machine
	bar_spr.reset( new hgeSprite( 0, 0, 0, 3, 2 ) );
	complete = 0;
}

void TimeMachine::Update( float dt )
{
	
}
void TimeMachine::Render()
{
	const DWORD filled_color = 0xff48e729;
	const DWORD unfilled_color = 0xffe83775;
	
	for( int n = 1; n < 7; ++n ) {
		if( complete > 0.16 * n ) { RenderBar( filled_color, n - 1 ); }
		else { RenderBar( unfilled_color, n - 1 ); }
	} 
	spr->spr->Render( pos.x, pos.y );
}

void TimeMachine::RenderBar( DWORD col, int n )
{
	const int x_off = 3;
	const int y_off = 24;
	const int y_bar_diff = -3;
	
	bar_spr->SetColor( col );
	bar_spr->Render( pos.x + x_off, pos.y + y_off + y_bar_diff * n );
}
