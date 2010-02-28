#include "GameComplete.hpp"
#include "World.hpp"
#include "Tree/Game.hpp"

GameComplete::GameComplete( World *w, boost::shared_ptr<SpriteLoader> spr_loader ) : world( w )
{
	shade.reset( new hgeSprite( 0, 0, 0, 800, 600 ) );
	shade->SetColor( 0x70000000 );
	
	is_active = false;
	
	pos = 0;
	
	fnt.reset( new hgeFont( "fnt/visitor20.fnt" ) );
	
	head = spr_loader->Get( "menu_pointer" );
	
	complete.Load( "sound/fanfar.wav" );
	failure.Load( "sound/fart.wav" );
}

bool GameComplete::HandleEvent( hgeInputEvent &e )
{
	if( e.type == INPUT_KEYDOWN ) {
		switch( e.key ) {
			case HGEK_LEFT:
				--pos;
				if( pos < 0 ) pos = 0;
				break;
			case HGEK_RIGHT:
				++pos;
				if( pos > 1 ) pos = 1;
				break;
			case HGEK_ENTER:
				if( pos == 0 ) NewGame();
				else if( pos == 1 ) Exit();
				is_active = false;
				break;
		}
	}
	
	return false;
}

void GameComplete::Play( bool p )
{
	success = p;
	is_active = true;
	
	if( success ) hge->Effect_Play( complete );
	else hge->Effect_Play( failure );
}
bool GameComplete::IsActive()
{
	return is_active;
}

void GameComplete::Update( float dt )
{
	
}
void GameComplete::Render()
{
	shade->Render(0,0);
	
	if( success ) {
		Show( 400, 140, "Puh!", 0xffffffff );
		Show( 400, 170, "You've survived Valentine again!", 0xffffffff );
		Show( 400, 200, "Play again?", 0xffffffff );
	}
	else {
		Show( 400, 140, "Meh!", 0xffffffff );
		Show( 400, 170, "Valentine owned you again!", 0xffffffff );
		Show( 400, 200, "Try again?", 0xffffffff );
	}
	
	const int yeah_x = 360;
	const int nah_x = 440;
	const int answer_y = 230;
	const int head_yeah_x = 305;
	const int head_nah_x = 395;
	const int head_y = 225;
	
	if( pos == 0 ) {
		Show( yeah_x, answer_y, "Yeah!", 0xffade848 );
		Show( nah_x, answer_y, "Nah", 0xffffffff );
		head->spr->Render( head_yeah_x, head_y );
	}
	else {
		Show( yeah_x, answer_y, "Yeah!", 0xffffffff );
		Show( nah_x, answer_y, "Nah", 0xffade848 );
		head->spr->Render( head_nah_x, head_y );
	}
}

void GameComplete::NewGame()
{
	world->NewGame();
}
void GameComplete::Exit()
{
	Tree::Game::Instance()->Exit();
}

void GameComplete::Show( int x, int y, std::string what, DWORD color )
{
	fnt->SetColor( 0xff000000 );
	fnt->Render( x + 1, y + 1, HGETEXT_CENTER, what.c_str() );
	fnt->SetColor( color );
	fnt->Render( x, y, HGETEXT_CENTER, what.c_str() );
}
