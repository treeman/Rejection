#include "Tweaks.hpp"
#include "Tree/Errorhandling.hpp"

Tweaks::Tweaks() 
{ 
	if( luaL_dofile( L, "tweaks.lua" ) ) {
		const char *str = lua_tostring( L, -1 );
		lua_pop( L, -1 );
		throw( Error::lua_error( str ) );
	}
}

LuaState Tweaks::Lua()
{
	return L;
}
