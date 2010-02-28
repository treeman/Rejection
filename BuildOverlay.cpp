#include "BuildOverlay.hpp"
#include "World.hpp"

#include <boost/foreach.hpp>

BuildOverlay::BuildOverlay( World *w, boost::shared_ptr<SpriteLoader> spr_loader, Vec2D p ) :
	world( w ), is_active( true ), pos( p )
{
	build_background = spr_loader->Get( "build_background" );
	trap_shade.reset( new hgeSprite( 0, 0, 0, 32, 32 ) );
	trap_shade->SetColor( 0x90000000 );
	trap_highlight = spr_loader->Get( "trap_highlight" );
	cancel = spr_loader->Get( "trap_cancel" );
	
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	
	trap_factory.reset( new TrapFactory( spr_loader ) );
	
	TrapFactory::Traps infos = trap_factory->GetTraps();
	BOOST_FOREACH( TrapInfo i, infos ) {
		boost::shared_ptr<Trap> trap = trap_factory->CreateTrap( i );
		traps.push_back( trap );
	}
	
	selection_pos = 0;
}

bool BuildOverlay::HandleEvent( hgeInputEvent &e )
{
	//this is really really ugly but hey, it works
	//should probably initiate and handle it from inside the dude controller
	//but why change it when it works? well, at least not now when I've got only a few hours left!!!
	//raaawwrrr
	if( !is_active ) {
		if( world->IsDudeFacingBuildableTile() && e.type == INPUT_KEYDOWN && e.key == HGEK_SPACE  ) {
			Activate();
			return false;
		}
		else {
			return true;
		}
	}
	
	if( e.type == INPUT_KEYDOWN ) {
		switch( e.key ) {
			case HGEK_ESCAPE:
			case HGEK_UP:
			case HGEK_DOWN:
				is_active = false;
				return true;
			case HGEK_LEFT:
				Left();
				break;
			case HGEK_RIGHT:
				Right();
				break;
			case HGEK_ENTER:
			case HGEK_SPACE:
				Action();
				break;
		}
	}
	
	return false;
}

bool BuildOverlay::IsActive()
{
	return is_active;
}
void BuildOverlay::Activate()
{
	is_active = true;
	selection_pos = 0;
}
void BuildOverlay::Deactivate()
{
	is_active = false;
	selection_pos = 0;
}

void BuildOverlay::Update( float dt )
{
	if( !is_active ) return;
}
void BuildOverlay::Render()
{
	if( !is_active ) return;
	
	build_background->spr->Render( pos.x, pos.y );
	
	const int x_off = 5;
	const int y_off = 4;
	
	const int x_next = 32;
	
	cancel->spr->Render( pos.x + x_off, pos.y + y_off );
	
	for( int n = 0; n < traps.size(); ++n ) {
		traps[n]->SetPos( Vec2D( pos.x + x_off + x_next * (n + 1), pos.y + y_off ) );
		traps[n]->Render();
	}
	
	trap_highlight->spr->Render( pos.x + x_off + x_next * selection_pos, pos.y + y_off );
}

void BuildOverlay::Left()
{
	if( selection_pos > 0 ) --selection_pos;
	else selection_pos = traps.size();
}
void BuildOverlay::Right()
{
	if( selection_pos < traps.size() ) ++selection_pos;
	else selection_pos = 0;
}
void BuildOverlay::Action()
{
	if( selection_pos < 1 ) { Deactivate(); }
	else {
		world->BuyTrap( trap_factory->CreateTrap( traps[selection_pos - 1]->GetInfo() ) );
		Deactivate();
	}
}
