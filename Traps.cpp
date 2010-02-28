#include "Traps.hpp"
#include "Tweaks.hpp"
#include "Tree/Log.hpp"

BlowerTrap::BlowerTrap( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr = spr_loader->Get( "blower_trap" );
	spr->spr->SetHotSpot( 16, 16 );
}

bool BlowerTrap::IsWalkable() { return false; }
bool BlowerTrap::IsSeeThrough() { return false; }

void BlowerTrap::Activate()
{
	L_ << "blower activated!!";
}

void BlowerTrap::Render()
{
	float rotation = 0;
	if( dir == Vec2D::left ) rotation = 3 * math::PI_2;
	else if( dir == Vec2D::right ) rotation = math::PI_2;
	else if( dir == Vec2D::up ) rotation = math::PI;
	else if( dir == Vec2D::down ) rotation = 0;
	
	spr->spr->RenderEx( pos.x + 16, pos.y + 16, rotation );
}

MagnetTrap::MagnetTrap( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr = spr_loader->Get( "magnet_trap" );
	spr->spr->SetHotSpot( 16, 16 );
}

bool MagnetTrap::IsWalkable() { return false; }
bool MagnetTrap::IsSeeThrough() { return false; }

void MagnetTrap::Render()
{
	float rotation = 0;
	if( dir == Vec2D::left ) rotation = 3 * math::PI_2;
	else if( dir == Vec2D::right ) rotation = math::PI_2;
	else if( dir == Vec2D::up ) rotation = math::PI;
	else if( dir == Vec2D::down ) rotation = 0;
	
	spr->spr->RenderEx( pos.x + 16, pos.y + 16, rotation );
}

PressurePad::PressurePad( boost::shared_ptr<SpriteLoader> spr_loader )
{
	spr = spr_loader->Get( "pressure_pad" );
}

bool PressurePad::IsWalkable() { return true; }
bool PressurePad::IsSeeThrough() { return true; }

int PressurePad::GetActivationRadius()
{
	if( IsActive() ) {
		return (int)TWEAKS->GetFloat( "pressure_pad_radius" );
	}
	else { return 0; }
}
void PressurePad::Activate()
{
	t.Restart();
}
void PressurePad::Deactivate()
{
	t.Stop();
}
bool PressurePad::IsActive()
{
	if( t.IsStarted() && t.GetTime() > TWEAKS->GetFloat( "pressure_pad_activation_time" ) ) {
		return true;
	}
	else { return false; }
}

void PressurePad::WalkOver()
{
	Activate();
}

void PressurePad::Render()
{
	spr->spr->Render( pos.x, pos.y );
}
