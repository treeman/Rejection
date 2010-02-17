#include <time.h>

#include "Tree/Game.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Log.hpp"

using Tree::Game;

Game::Game() : exit_called( false )
{
	
}
Game::~Game()
{
	
}

bool Game::Logic()
{
	const float dt = hge->Timer_GetDelta();
	
	//set the new state to handle stuff
	curr_state = Top();
	
	if( curr_state ) {
		
		hgeInputEvent event;
		while( hge->Input_GetEvent( &event ) ) 
		{
			if( console->HandleEvent( event ) ) {
				curr_state->HandleEvent( event );
			}
		}
		
		curr_state->Update( dt );
		console->Update( dt );
	}
	
	return ShallExit();
}

bool Game::Render()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear( 0xFF000000 );
	
	if( curr_state ) curr_state->Render();
	console->Render();
	game_debug->Render();

	hge->Gfx_EndScene();
	return false;
}

void Game::Init( int width, int height, bool windowed, std::string title, std::string settings_file )
{
	hge->System_SetState( HGE_DONTSUSPEND, true );
	hge->System_SetState( HGE_SHOWSPLASH, false );
	hge->System_SetState( HGE_HIDEMOUSE, false );
	
	//avoid flashing back n forth
	hge->System_SetState( HGE_WINDOWED, true );
	
	hge->Random_Seed( time( NULL ) );
	srand( time( NULL ) );

	SETTINGS->SetValue( "video_screen_width", width );
	SETTINGS->SetValue( "video_screen_height", height );
	SETTINGS->SetValue( "video_screen_windowed", windowed );
	
	SETTINGS->SetValue( "sound_enabled", true );
	SETTINGS->SetValue( "stream_volume", 100 );
	SETTINGS->SetValue( "music_volume", 100 );
	SETTINGS->SetValue( "effect_volume", 100 );
	
	if( settings_file != "" ) {
		try {
			SETTINGS->ParseFile( settings_file );
		}
		catch( Error::file_not_found &e ) { 
			L_ << "Oops, you've deleted the settings file '" + settings_file + "'";
			L_ << "God will not forgive you!!! :@";
		}
	}
	
	SETTINGS->SetValue( "video_screen_bpp", 32 );
	SETTINGS->SetValue( "video_caption_title", title );
}
void Game::InitPostHge()
{
	curr_state = Top();
	
	window_manager.reset( new Tree::WindowManager() );
	sound_manager.reset( new Tree::SoundManager() );
	
	console.reset( new Tree::Console() );
	
	console->AddHistory( "starting up the ownage game environment" );
	console->AddHistory( "screen res: " + 
		SETTINGS->GetSetting( "video_screen_width" ) + "x" + 
		SETTINGS->GetSetting( "video_screen_height" ) + " bpp: " +
		SETTINGS->GetSetting( "video_screen_bpp" )
	);
	
	game_debug.reset( new Tree::GameDebug() );
}

void Game::Pop()
{
	state_list.pop_front();
}
void Game::Push( boost::shared_ptr<GameState> state )
{
	state_list.push_front( state );
}
boost::shared_ptr<Tree::GameState> Game::Top()
{
	if( !state_list.empty() ) {
		return state_list.front();
	}
	else {
		boost::shared_ptr<GameState> empty;
		return empty;
	}
}

void Game::Exit()
{
	exit_called = true;
}
bool Game::ShallExit() const
{
	return state_list.empty() || exit_called;
}
