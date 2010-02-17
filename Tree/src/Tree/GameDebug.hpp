#pragma once

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Settings.hpp"
#include "Dator.hpp"

namespace Tree 
{
	class GameDebug {
	public:
		GameDebug();
		
		void Update( float dt );
		void Render();
	private:
		HgeObj hge;
		
		boost::shared_ptr<Dator<bool> > show_mouse_pos;
		boost::shared_ptr<Dator<bool> > show_fps;
		
		boost::shared_ptr<hgeFont> arial10;
		boost::shared_ptr<hgeFont> visitor20;
	};
}
