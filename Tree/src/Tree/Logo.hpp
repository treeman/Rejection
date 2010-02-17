#ifndef LOGO_HPP_INCLUDED
#define LOGO_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "Tree/GameState.hpp"
#include "Hge/Hge.hpp"
#include "Tree/Timer.hpp"

namespace Tree {

	class Logo : public Tree::GameState {
	public:
		Logo();
		~Logo();
		
		bool HandleEvent( hgeInputEvent &e );
		
		void Update( float dt );
		void Render();
	private:
		Timer t;
		
		TexObj logo_tex;
		boost::shared_ptr<hgeSprite> logo;
		float x, y;
		
		boost::shared_ptr<hgeSprite> fade;
		int fade_dir;
		DWORD fade_color;
		
		HgeObj hge;
	};
	
}

#endif
