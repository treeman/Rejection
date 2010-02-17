#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <string>

#include "Hge/Hge.hpp"
#include "Dator.hpp"

namespace Tree 
{
	class WindowManager {
	public:
		WindowManager();
		~WindowManager();
		
		std::string SetWindowed( bool predicate );
		std::string SetScreenWidth( int val );
		std::string SetScreenHeight( int val );
		std::string SetScreenBPP( int val );
		std::string SetScreenTitle( std::string val );
	private:
		HgeObj hge;
		
		boost::shared_ptr<Dator<int> > width;
		boost::shared_ptr<Dator<int> > height;
		boost::shared_ptr<Dator<int> > bpp;
		boost::shared_ptr<Dator<bool> > is_windowed;
		boost::shared_ptr<Dator<std::string> > title;
	};
}
