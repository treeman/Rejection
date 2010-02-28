#include "InfoBar.hpp"
#include "Tree/Log.hpp"

InfoBar::InfoBar( boost::shared_ptr<SpriteLoader> spr_loader )
{
	life_spr = spr_loader->Get( "dude_life" );
	life = 5;
	money = 1337;
	money_fnt.reset( new hgeFont( "fnt/visitor15.fnt" ) );
	background = spr_loader->Get( "brick" );
	
	die.Load( "sound/bounce.wav" );
	katjing.Load( "sound/katjing.wav" );
}

void InfoBar::SetLife( int n )
{
	if( n < life ) hge->Effect_Play( die );
	life = n;
}
void InfoBar::SetMoney( int n )
{
	money = n;
//	hge->Effect_Play( katjing );
}
void InfoBar::Render()
{
	//no not the owl!!!
	background->spr->Render(0,0);
	
	for( int n = 0; n < life; ++n ) {
		life_spr->spr->Render( 100 + n * 30, 0 );
	}
	
	money_fnt->SetColor( 0xff23db4a );
	money_fnt->printf( 790, 8, HGETEXT_RIGHT, "%i $", money );
}
