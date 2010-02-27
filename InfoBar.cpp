#pragma once

#include "InfoBar.hpp"

InfoBar::InfoBar( boost::shared_ptr<SpriteLoader> spr_loader )
{
	life_spr = spr_loader->Get( "dude_head" );
	life = 5;
	money = 1337;
	money_fnt.reset( new hgeFont( "fnt/visitor15.fnt" ) );
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
	for( int n = 0; n < life; ++n ) {
		life_spr->spr->Render( 110 + n * 30, 20 );
	}
	
	money_fnt->SetColor( 0xff27cd2b );
	money_fnt->printf( 480, 20, HGETEXT_RIGHT, "%i $", money );
}
