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

int BlowerTrap::GetBlowLength()
{
	if( IsActive() ) {
		return (int)TWEAKS->GetFloat( "blower_length" );
	}
	else { return 0; }
}
Vec2D BlowerTrap::GetBlowDir()
{
	return GetFaceDir();
}

void BlowerTrap::Activate()
{
	t.Restart();
}
void BlowerTrap::Deactivate()
{
	t.Stop();
}

bool BlowerTrap::IsActive()
{
	if( t.IsStarted() && t.GetTime() < TWEAKS->GetFloat( "blower_activation_time" ) ) {
//		L_ << "oh blower is active alright!!";
		return true;
	}
	else { return false; }
}

void BlowerTrap::Render()
{
	float rotation = 0;
	if( dir == Vec2D::left ) rotation = math::PI_2;
	else if( dir == Vec2D::right ) rotation = 3 * math::PI_2;
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

int MagnetTrap::GetBlowLength()
{
	if( IsActive() ) {
		return (int)TWEAKS->GetFloat( "magnet_length" );
	}
	else { return 0; }
}
Vec2D MagnetTrap::GetBlowDir()
{
	return -GetFaceDir();
}

void MagnetTrap::Activate()
{
	t.Restart();
}
void MagnetTrap::Deactivate()
{
	t.Stop();
}

bool MagnetTrap::IsActive()
{
	if( t.IsStarted() && t.GetTime() < TWEAKS->GetFloat( "magnet_activation_time" ) ) {
//		L_ << "oh blower is active alright!!";
		return true;
	}
	else { return false; }
}

void MagnetTrap::Render()
{
	float rotation = 0;
	if( dir == Vec2D::left ) rotation = math::PI_2;
	else if( dir == Vec2D::right ) rotation = 3 * math::PI_2;
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
//	L_ << "pressure pad activated!!";
}
void PressurePad::Deactivate()
{
	t.Stop();
}
bool PressurePad::IsActive()
{
	if( t.IsStarted() && t.GetTime() < TWEAKS->GetFloat( "pressure_pad_activation_time" ) ) {
//		L_ << "yes pressure pad is active";
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
