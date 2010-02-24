#include "Sprite.hpp"
#include "Tree/Log.hpp"

#include <boost/assert.hpp>

Sprite::Sprite( std::string file, float x, float y, float w, float h, DWORD col ) : tex( file ), 
	spr( new hgeSprite( tex, x, y, w, h ) ), color( col )
{
	if( col != 0 ) spr->SetColor( col );
}

SpriteLoader::SpriteLoader() { }
	
void SpriteLoader::Load( std::string lua_file ) throw( Error::lua_error & )
{
	LuaState L;
	
	if( luaL_dofile( L, lua_file.c_str() ) ) {
		const char *str = lua_tostring( L, -1 );
		lua_pop( L, -1 );
		throw( Error::lua_error( str ) );
	}
	
	lua_getglobal( L, "sprites" );
	for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) ) 
	{
		//parse a sprite here
		std::string name, path;
		float x = 0, y = 0, w = 0, h = 0;
		DWORD color = 0;
		
		bool is_valid = true;
		
		lua_pushstring( L, "name" );
		lua_gettable( L, -2 );
		if( lua_isstring( L, -1 ) ) {
			name = lua_tostring( L, -1 );
		} else { is_valid = false; }
		lua_pop( L, 1 );
		
		lua_pushstring( L, "path" );
		lua_gettable( L, -2 );
		if( lua_isstring( L, -1 ) ) {
			path = lua_tostring( L, -1 );
		} else { is_valid = false; }
		lua_pop( L, 1 );
		
		lua_pushstring( L, "color" );
		lua_gettable( L, -2 );
		if( lua_isnumber( L, -1 ) ) {
			color = (DWORD)lua_tonumber( L, -1 );
		}
		lua_pop( L, 1 );
		
		lua_pushstring( L, "x" );
		lua_gettable( L, -2 );
		if( lua_isnumber( L, -1 ) ) {
			x = (float)lua_tonumber( L, -1 );
		}
		lua_pop( L, 1 );
		
		lua_pushstring( L, "y" );
		lua_gettable( L, -2 );
		if( lua_isnumber( L, -1 ) ) {
			y = (float)lua_tonumber( L, -1 );
		}
		lua_pop( L, 1 );
		
		lua_pushstring( L, "w" );
		lua_gettable( L, -2 );
		if( lua_isnumber( L, -1 ) ) {
			w = (float)lua_tonumber( L, -1 );
		}
		lua_pop( L, 1 );
		
		lua_pushstring( L, "h" );
		lua_gettable( L, -2 );
		if( lua_isnumber( L, -1 ) ) {
			h = (float)lua_tonumber( L, -1 );
		}
		lua_pop( L, 1 );
		
		if( is_valid ) {
			boost::shared_ptr<Sprite> spr( new Sprite( path, x, y, w, h, color ) );
			sprite_map[name] = spr;
		}
	}
}

boost::shared_ptr<Sprite> SpriteLoader::Get( std::string name )
{
	SpriteMap::iterator it = sprite_map.find( name );
	if( it == sprite_map.end() ) {
		throw( Error::sprite_not_found( ( "sprite " + name + " not found" ).c_str() ) );
	}
	else { return it->second; }
}
