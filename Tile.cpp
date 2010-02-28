#include "Tile.hpp"

Tile::Tile( Vec2D p, boost::shared_ptr<SpriteLoader> spr_loader ) : pos( p )
{
	flow = spr_loader->Get( "flow" );
	flow->spr->SetHotSpot( 16, 16 );
	flow_power = 0;
}

boost::shared_ptr<TileObject> Tile::Attachment()
{
	return attachment;
}

bool Tile::Attach( boost::shared_ptr<TileObject> a )
{
	if( attachment ) { return false; }
	else {
		attachment = a;
		attachment->SetPos( pos );
		return true;
	}
}
void Tile::Detach()
{
	attachment.reset();
}
bool Tile::IsWalkable()
{
	if( attachment ) return attachment->IsWalkable();
	else return true;
}
bool Tile::IsSeeThrough()
{
	if( attachment ) return attachment->IsSeeThrough();
	else return true;
}

float Tile::GetFlowPower()
{
	return flow_power;
}
Vec2D Tile::GetFlowDirection()
{
	return flow_dir;
}
void Tile::SetFlowDirection( Vec2D dir, float power )
{
	if( flow_dir == Vec2D::zero || power > flow_power ) {
		flow_dir = dir;
		flow_power = power;
	}
}
void Tile::ClearFlow()
{
	flow_dir = Vec2D::zero;
}

Tree::Rect Tile::Bounds() const 
{ 
	return Tree::Rect( pos.x, pos.y, 32, 32 );
}

void Tile::RenderFlow()
{
	if( flow_dir == Vec2D::zero ) return;
	
	float rotation = 0;
	if( flow_dir == Vec2D::left ) rotation = math::PI;
	else if( flow_dir == Vec2D::right ) rotation = 0;
	else if( flow_dir == Vec2D::up ) rotation = 3 * math::PI_2;
	else if( flow_dir == Vec2D::down ) rotation = math::PI_2;
	
	flow->spr->RenderEx( pos.x + 16, pos.y + 16, rotation );
}
