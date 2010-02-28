#include "TrapFactory.hpp"
#include "Tweaks.hpp"
#include "Traps.hpp"

TrapFactory::TrapFactory( boost::shared_ptr<SpriteLoader> l ) :
	spr_loader( l )
{
	TrapInfo i;
	i.name = "magnet";
	i.cost = TWEAKS->GetFloat( "magnet_cost" );
	traps.push_back( i );
	i.Reset();
	
	i.name = "blower";
	i.cost = TWEAKS->GetFloat( "blower_cost" );
	traps.push_back( i );
	i.Reset();
	
	i.name = "pressure_pad";
	i.cost = TWEAKS->GetFloat( "pressure_pad_cost" );
	traps.push_back( i );
	i.Reset();
}

TrapFactory::Traps TrapFactory::GetTraps()
{
	return traps;
}

boost::shared_ptr<Trap> TrapFactory::CreateTrap( TrapInfo info )
{
	boost::shared_ptr<Trap> trap;
	if( info.name == "magnet" ) {
		trap.reset( new MagnetTrap( spr_loader ) );
		trap->SetInfo( info );
	}
	else if( info.name == "blower" ) {
		trap.reset( new BlowerTrap( spr_loader ) );
		trap->SetInfo( info );
	}
	else if( info.name == "pressure_pad" ) {
		trap.reset( new PressurePad( spr_loader ) );
		trap->SetInfo( info );
	}
	return trap;
}
