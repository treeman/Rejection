#pragma once

#include "Hge/Hge.hpp"

#include "Tree/Settings.hpp"
#include "Tree/Dator.hpp"

#include "Grid.hpp"
#include "Tile.hpp"
#include "Dude.hpp"
#include "Girl.hpp"
#include "GirlController.hpp"
#include "TimeMachine.hpp"
#include "WorldListener.hpp"

class World {
public:
	World( boost::shared_ptr<SpriteLoader> spr_loader );
	
	boost::shared_ptr<Dude> GetDude();
	
	void AddListener( WorldListener *l );
	
	void NewGame();
	
	bool GameComplete();
	bool GameOver();
	
	void Update( float dt );
	void Render();
private:
	void UpdateDude( boost::shared_ptr<Dude> o, float dt );

	void UpdatePerson( boost::shared_ptr<Person> o, float dt );
	void RenderPerson( boost::shared_ptr<Person> o );
	
	void CheckCollisions( boost::shared_ptr<MovingObject> o );
	bool Collision( Tree::Rect bounds, int x, int y );
	
	Grid grid;
	
	boost::shared_ptr<Dude> dude;
	boost::shared_ptr<hgeFont> fnt;
	
	void SpawnGirl();
	void KillGirl( boost::shared_ptr<Girl> girl );
	
	boost::shared_ptr<SpriteLoader> spr_loader;
	
	typedef std::vector<boost::shared_ptr<Girl> > Girls;
	Girls girls;
	boost::shared_ptr<GirlController> girl_controller;
	
	typedef boost::shared_ptr<Tile> TilePtr;
	typedef std::vector<TilePtr> Tiles;
	typedef std::vector<Tiles> TileGrid;
	
	void InitTiles();
	void Geekify();
	void Geekify( int x, int y );
	
	bool IsWalkable( GridPos p ) { return IsWalkable( p.x, p.y ); }
	bool IsWalkable( int x, int y );
	
	bool IsSeeThrough( GridPos p ) { return IsSeeThrough( p.x, p.y ); }
	bool IsSeeThrough( int x, int y );
	
	bool IsValid( GridPos p ) { return IsValid( p.x, p.y ); }
	bool IsValid( int x, int y );
	
	TileGrid tiles;
	
	boost::shared_ptr<TimeMachine> time_machine;
	
	typedef std::vector<WorldListener*> Listeners;
	Listeners listeners;
	
	boost::shared_ptr<Sprite> dude_working;
	bool WorkingOnTimeMachine();
	
	void InitDebug();
	boost::shared_ptr<Tree::Dator<bool> > show_mouse_grid;
	boost::shared_ptr<Tree::Dator<bool> > show_bounds;
	
	HgeObj hge;
	
	boost::shared_ptr<Tree::Dator<bool> > debug_dude;
};
