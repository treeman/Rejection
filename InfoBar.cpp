#pragma once

#include "InfoBar.hpp"

InfoBar::InfoBar( boost::shared_ptr<SpriteLoader> spr_loader )
{
	life_spr = spr_loader->Get( "dude_life" );
	life = 5;
	money = 1337;
	money_fnt.reset( new hgeFont( "fnt/visitor15.fnt" ) );
	background = spr_loader->Get( "brick" );
}

void InfoBar::SetLife( int n )
{
	life = n;
}
void InfoBar::SetMoney( int n )
{
	money = n;
}
void InfoBar::Render()
{
	//no not the owl!!!
	background->spr->Render(0,0);
	
	for( int n = 0; n < life; ++n ) {
		life_spr->spr->Render( 100 + n * 30, 0 );
	}
	
	money_fnt->SetColor( 0xff23db4a );
	money_fnt->printf( 480, 8, HGETEXT_RIGHT, "%i $", money );
}
