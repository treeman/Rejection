#include "Tree/Windowmanager.hpp"
#include "Tree/Settings.hpp"

using Tree::WindowManager;

WindowManager::WindowManager()
{
	width.reset( new Dator<int>( 800, boost::bind( &WindowManager::SetScreenWidth, this, _1 ) ) );
	height.reset( new Dator<int>( 600, boost::bind( &WindowManager::SetScreenHeight, this, _1 ) ) );
	bpp.reset( new Dator<int>( 32, boost::bind( &WindowManager::SetScreenBPP, this, _1 ) ) );
	is_windowed.reset( new Dator<bool>( true, boost::bind( &WindowManager::SetWindowed, this, _1 ) ) );
	title.reset( new Dator<std::string>( "W00t nuthing initialized!", boost::bind( &WindowManager::SetScreenTitle, this, _1 ) ) );

    SETTINGS->RegisterVariable( "video_screen_width", boost::weak_ptr<BaseDator>( width ) );
	SETTINGS->RegisterVariable( "video_screen_height", boost::weak_ptr<BaseDator>( height ) );
	SETTINGS->RegisterVariable( "video_screen_bpp", boost::weak_ptr<BaseDator>( bpp ) );
    SETTINGS->RegisterVariable( "video_screen_windowed", boost::weak_ptr<BaseDator>( is_windowed ) );
	SETTINGS->RegisterVariable( "video_caption_title", boost::weak_ptr<BaseDator>( title ) );
}

WindowManager::~WindowManager()
{
	
}

std::string WindowManager::SetWindowed( bool predicate )
{
	hge->System_SetState( HGE_WINDOWED, predicate );
	if( predicate ) {
		return "you're now surfing machine code in windowed mode";
	}
	else {
		return "you're now surfing machine code in fullscreen";
	}
}
std::string WindowManager::SetScreenWidth( int val )
{
	hge->System_SetState( HGE_SCREENWIDTH, val );
	return "nananana... you can't alter it here :)";
}
std::string WindowManager::SetScreenHeight( int val )
{
	hge->System_SetState( HGE_SCREENHEIGHT, val );
	return "nananana... you can't alter it here :()";
}
std::string WindowManager::SetScreenBPP( int val )
{
	hge->System_SetState( HGE_SCREENBPP, val );
	return "error: can't set bpp value";
}
std::string WindowManager::SetScreenTitle( std::string val )
{
	hge->System_SetState( HGE_TITLE, val.c_str() );
	return "setting window title to '" + val + "'";
}
