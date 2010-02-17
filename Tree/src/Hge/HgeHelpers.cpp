#include <vector>

#include "Hge/Hge.hpp"
#include "Tree/Vec2D.hpp"

void hgeh::render_rect( HGE *hge, float x1, float y1, float x2, float y2, DWORD color )
{
	//-1 is a ugly hack to make a "perfect" square outline, or else there's a gap top left
	hge->Gfx_RenderLine( x1 - 1, y1, x2, y1, color );
	hge->Gfx_RenderLine( x2, y1, x2, y2, color );
	hge->Gfx_RenderLine( x2, y2, x1, y2, color );
	hge->Gfx_RenderLine( x1, y2, x1, y1, color );
}

void hgeh::render_solid_rect( HGE *hge, float x1, float y1, float x2, float y2, DWORD color )
{
	hgeQuad q;
	q.blend = BLEND_DEFAULT;
	q.tex = 0;
	
	hgeVertex v;
	v.col = color;
	v.tx = 0.0;
	v.ty = 0.0;
	
	q.v[0] = q.v[1] = q.v[2] = q.v[3] = v;
	
	q.v[0].x = x1; q.v[0].y = y1;
	q.v[1].x = x2; q.v[1].y = y1;
	q.v[2].x = x2; q.v[2].y = y2;
	q.v[3].x = x1; q.v[3].y = y2;
	
	hge->Gfx_RenderQuad( &q );
}

void hgeh::render_circle( HGE *hge, float x, float y, float radius, int segments, DWORD color )
{
	const float increment = math::PI2 / segments;
	float theta = 0.0f;
	
	const Vec2D center( x, y );
	
	typedef std::vector<Vec2D> Positions;
	Positions positions;
	for( int i = 0; i < segments; ++i )
	{
		Vec2D p = Vec2D( std::cos( theta ), std::sin( theta ) );
		p *= radius;
		p += center;
		positions.push_back( p );
		theta += increment;
	}
	
	render_lines( hge, positions, color, true );
}

void hgeh::render_circle_slice( HGE *hge, float x, float y, float radius, int segments, float begin, float end, DWORD color )
{
	const float increment = ( end - begin ) / segments;
	float theta = begin;
	
	const Vec2D center( x, y );
	
	typedef std::vector<Vec2D> Positions;
	Positions positions;
	for( int i = 0; i < segments + 1; ++i )
	{
		Vec2D p = Vec2D( std::cos( theta ), std::sin( theta ) );
		p *= radius;
		p += center;
		positions.push_back( p );
		theta += increment;
	}
	
	render_lines( hge, positions, color );
	
	Vec2D first = Vec2D( std::cos( begin ), std::sin( begin ) ) * radius + center;
	Vec2D last = Vec2D( std::cos( end ), std::sin( end ) ) * radius + center;
	//-1 correct point
	hge->Gfx_RenderLine( center.x - 1, center.y, first.x, first.y, color );
	hge->Gfx_RenderLine( center.x, center.y, last.x, last.y, color );
}

void hgeh::render_solid_circle( HGE *hge, float x, float y, float radius, int segments, DWORD color )
{
	render_solid_circle_slice( hge, x, y, radius, segments, 0.0f, math::PI2, color );
}

void hgeh::render_solid_circle_slice( HGE *hge, float x, float y, float radius, int segments, float begin, float end, DWORD color )
{
	const float increment = ( end - begin ) / segments;
	float theta = begin;
	
	const Vec2D center( x, y );
	
	typedef std::vector<Vec2D> Positions;
	Positions positions;
	for( int i = 0; i < segments + 1; ++i )
	{
		Vec2D p = Vec2D( std::cos( theta ), std::sin( theta ) ) * radius + center;
		positions.push_back( p );
		theta += increment;
	}
	
	for( Positions::iterator it = positions.begin(); it != positions.end(); )
	{
		Vec2D p1 = *it;
		++it;
		Vec2D p2;
		if( it != positions.end() ) {
			p2 = *it;
		}
		else {
			p2 = *positions.begin();
		}
		
		hgeTriple t;
		t.blend = BLEND_DEFAULT;
		t.tex = 0;
		
		hgeVertex v;
		v.col = color;
		v.tx = 0.0;
		v.ty = 0.0;
		
		v.x = center.x;
		v.y = center.y;
		t.v[0] = v;
		
		v.x = p1.x;
		v.y = p1.y;
		t.v[1] = v;
		
		v.x = p2.x;
		v.y = p2.y;
		t.v[2] = v;
		
		hge->Gfx_RenderTriple( &t );
	}
}

void hgeh::render_lines( HGE *hge, std::vector<Vec2D> positions, DWORD color, bool loop )
{
	typedef std::vector<Vec2D> Positions;
	
	for( Positions::iterator it = positions.begin(); it != positions.end(); )
	{
		Vec2D p1 = *it;
		++it;
		Vec2D p2;
		if( it != positions.end() ) {
			p2 = *it;
		}
		else {
			if( loop ) p2 = *positions.begin();
			else return;
		}
		hge->Gfx_RenderLine( p1.x, p1.y, p2.x, p2.y, color );
	}
}

void hgeh::render_triples( HGE *hge, std::vector<Vec2D> positions, DWORD color )
{
	typedef std::vector<Vec2D> Positions;
	
	
}
