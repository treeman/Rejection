#pragma once

#include <boost/shared_ptr.hpp>

#include "TileObject.hpp"
#include "Sprite.hpp"

class TimeMachine : public TileObject {
public:
	TimeMachine( boost::shared_ptr<SpriteLoader> spr_loader );
	
	bool IsWalkable() { return false; }
	bool IsSeeThrough() { return false; }
	
	void SetCompletePerc( float perc ) {
		complete = perc;
	}
	float GetCompletePerc() {
		return complete;
	}
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<Sprite> spr;
	
	void RenderBar( DWORD col, int n );
	boost::shared_ptr<hgeSprite> bar_spr;
	float complete;
};
