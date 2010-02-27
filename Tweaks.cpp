#include "Tweaks.hpp"
#include "Tree/Errorhandling.hpp"
#include "Lua/Lua.hpp"
#include "Tree/Log.hpp"

Tweaks::Tweaks() 
{ 
	LuaState L;
	if( luaL_dofile( L, "tweaks.lua" ) ) {
		const char *str = lua_tostring( L, -1 );
		lua_pop( L, -1 );
		throw( Error::lua_error( str ) );
	}
	
	lua_getglobal( L, "_G" );
	for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) ) 
	{
		if( lua_isnumber( L, -1 ) ) {
			floats[lua_tostring( L, -2 )] = (float)lua_tonumber( L, -1 );
		}
	}
}

float Tweaks::GetFloat( std::string s )
{
	FloatMap::iterator it = floats.find( s );
	if( it != floats.end() ) { return it->second; }
	else {
		throw( Error::setting_not_found( (s + " wasn't found in tweaks.lua").c_str() ) );
	}
}
