#pragma once

#include "Box2D/Box2D.h"
#include "Hge/Hge.hpp"

namespace b2Debug 
{
	///hge uses a delayed rendering
	///with a separet update and rendering function
	///that's why we have to delay the rendering like this
	typedef std::vector<Vec2D> Points;
	
	//transform a box2D color to a hge color
	inline DWORD make_color( const b2Color& c, int alpha = 255 );
	
	struct Shape {
		virtual ~Shape() { }
		virtual void Render() = 0;
		
		HgeObj hge;
	};
	
	struct Poly : public Shape {
		Poly( const b2Vec2 *vs, int32 n, const b2Color& c ) {
			for( int i = 0; i < n; ++i ) {
				ps.push_back( vs[i] );
			}
			color = make_color( c );
		}
		Points ps;
		DWORD color;
		
		void Render();
	};
	struct SolidPolygon : public Poly {
		SolidPolygon( const b2Vec2 *vs, int32 n, const b2Color& c ) :
			Poly( vs, n, c ) 
		{ }
			
		void Render();
	};
	
	struct Circle : public Shape {
		Circle( const b2Vec2 &cent, float32 r, const b2Color& c ) :
			center( cent ),  radius( r ), color( make_color( c ) )
		{ }
		Vec2D center;
		float radius;
		DWORD color;
		
		void Render();
	};
	
	struct SolidCircle : public Circle {
		SolidCircle( const b2Vec2 &cent, float32 r, const b2Color& c ) :
			Circle( cent, r, c ) { }
			
		void Render();
	};
	
	struct Segment : public Shape {
		Segment( const b2Vec2& _p1, const b2Vec2& _p2, const b2Color& c ) :
			p1( _p1 ), p2( _p2 ), color( make_color( c ) )
		{ }
		Vec2D p1, p2;
		DWORD color;
		
		void Render();
	};

	class Drawer : public b2DebugDraw {
	public:
		void DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color );
		void DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color );
		void DrawCircle( const b2Vec2& center, float32 radius, const b2Color& color );
		void DrawSolidCircle( const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color );
		void DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color );
		void DrawXForm( const b2XForm& xf );
		
		//this will actually render everything
		void Render();
	private:
		typedef std::vector<boost::shared_ptr<Shape> > Shapes;
		Shapes shapes;
	};
}
