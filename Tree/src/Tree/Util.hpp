#pragma once

#include "Math.hpp"

namespace Tree
{
	template<class Iterator>
	Iterator random( Iterator first, Iterator last )
	{
		//will crash if first == last
		if( first == last ) {
			return first;
		}
		int n = 0;
		Iterator it = first;
		for( ; it != last; ++it ) {
			++n;
		}
		if( n == 1 ) {
			return first;
		}
		
		int r = math::irandom( 0, n - 1 );
		for( int i = 0; i < n; ++i, ++first ) { 
			if( i == r ) {
				return first;
			}
		}
		return first;
	}
	
	//transform a range [0-1] to [0-255] 
	inline float enbyten( float zero_to_one )
	{
		if( zero_to_one == 0 ) return 0;
		else return zero_to_one / 1.0f * 255;
	}
}
