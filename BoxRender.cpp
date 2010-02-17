#include "BoxRender.hpp"
#include "Hge/Hge.hpp"
#include "Tree/Log.hpp"
#include "Tree/Util.hpp"

#include <vector>
#include <boost/foreach.hpp>

using namespace b2Debug;

inline DWORD b2Debug::make_color( const b2Color& c, int alpha )
{
	return ARGB( alpha, Tree::enbyten( c.r ), Tree::enbyten( c.g ), Tree::enbyten( c.b ) );
}

void Poly::Render()
{
	hgeh::render_lines( hge, ps, color );
}
void SolidPolygon::Render()
{
	hgeh::render_lines( hge, ps, color );
}
void Circle::Render()
{
	hgeh::render_circle( hge, center.x, center.y, radius, 14, color );
}
void SolidCircle::Render()
{
	hgeh::render_solid_circle( hge, center.x, center.y, radius, 14, color );
}
void Segment::Render()
{
	hge->Gfx_RenderLine( p1.x, p1.y, p2.x, p2.y, color );
}

void Drawer::DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
	boost::shared_ptr<Shape> s( new Poly( vertices, vertexCount, color ) );
	shapes.push_back( s );
}

void Drawer::DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
	boost::shared_ptr<Shape> s( new SolidPolygon( vertices, vertexCount, color ) );
	shapes.push_back( s );
}

void Drawer::DrawCircle( const b2Vec2& center, float32 radius, const b2Color& color )
{
	boost::shared_ptr<Shape> s( new Circle( center, radius, color ) );
	shapes.push_back( s );
}

void Drawer::DrawSolidCircle( const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color )
{
	boost::shared_ptr<Shape> s( new SolidCircle( center, radius, color ) );
	shapes.push_back( s );
}

void Drawer::DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color )
{
	boost::shared_ptr<Shape> s( new Segment( p1, p2, color ) );
	shapes.push_back( s );
}

void Drawer::DrawXForm( const b2XForm& xf )
{
	
}

void Drawer::Render()
{
	BOOST_FOREACH( boost::shared_ptr<Shape> s, shapes ) {
		s->Render();
	}
	shapes.clear();
}
