#include "Tree/GameDebug.hpp"

using Tree::GameDebug;

GameDebug::GameDebug()
{
	show_mouse_pos.reset( new Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "mouse_pos_show", boost::weak_ptr<BaseDator>( show_mouse_pos ) );
	
	show_fps.reset( new Dator<bool>( false ) );
	SETTINGS->RegisterVariable( "fps_show", boost::weak_ptr<BaseDator>( show_fps ) );
	
	arial10.reset( new hgeFont( "fnt/arial10.fnt" ) );
	visitor20.reset( new hgeFont( "fnt/visitor20.fnt" ) );
}

void GameDebug::Update( float )
{
	
}
void GameDebug::Render()
{
	if( show_mouse_pos->Val() ) {
		float x, y;
		hge->Input_GetMousePos( &x, &y );
		arial10->SetColor( 0xffffffff );
		arial10->printf( 50, 5, HGETEXT_LEFT, "%.0f,%.0f", x, y );
	}
	
	if( show_fps->Val() ) {
		visitor20->SetColor( 0xffffffff );
		visitor20->printf( 5, 5, HGETEXT_LEFT, "%i", hge->Timer_GetFPS() );
	}
}
