#pragma once

#include "WorldListener.hpp"
#include "Sprite.hpp"

class InfoBar : public WorldListener {
public:
	InfoBar( boost::shared_ptr<SpriteLoader> spr_loader );
	
	void SetLife( int life );
	void SetMoney( int money );
	
	void Render();
private:
	boost::shared_ptr<Sprite> life_spr;
	int life;
	
	int money;
	boost::shared_ptr<hgeFont> money_fnt;
	
	boost::shared_ptr<Sprite> background;
};
