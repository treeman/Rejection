#ifndef HGEHELPERS_HPP_INCLUDED
#define HGEHELPERS_HPP_INCLUDED

#include "HgeIncl.hpp"
#include "Tree/Vec2D.hpp"

#include <vector>

namespace hgeh {
	
	void render_rect( HGE *hge, float x1, float y1, float x2, float y2, DWORD color );
	void render_solid_rect( HGE *hge, float x1, float y1, float x2, float y2, DWORD color );
	
	void render_circle( HGE *hge, float x, float y, float radius, int segments, DWORD color );
	void render_solid_circle( HGE *hge, float x, float y, float radius, int segments, DWORD color );
	
	void render_circle_slice( HGE *hge, float x, float y, float radius, 
		int segments, float begin, float end, DWORD color );
	void render_solid_circle_slice( HGE *hge, float x, float y, float radius, 
		int segments, float begin, float end, DWORD color );
		
	void render_lines( HGE *hge, std::vector<Vec2D> positions, DWORD color, bool loop = false );
	void render_triples( HGE *hge, std::vector<Vec2D> positions, DWORD color );
}

#endif
