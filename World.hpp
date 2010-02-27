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
	
	void Update( float dt );
	void Render();
private:
	void UpdatePerson( boost::shared_ptr<Person> o, float dt );
	void RenderPerson( boost::shared_ptr<Person> o );
	
	void CheckWorldBounds( boost::shared_ptr<MovingObject> o );
	
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
	
	void InitTiles( boost::shared_ptr<SpriteLoader> spr_loader );
	
	bool IsWalkable( GridPos p ) { IsWalkable( p.x, p.y ); }
	bool IsWalkable( int x, int y );
	
	bool IsSeeThrough( GridPos p ) { IsSeeThrough( p.x, p.y ); }
	bool IsSeeThrough( int x, int y );
	
	bool IsValid( GridPos p ) { IsValid( p.x, p.y ); }
	bool IsValid( int x, int y );
	
	TileGrid tiles;
	
	boost::shared_ptr<TimeMachine> time_machine;
	
	typedef std::vector<WorldListener*> Listeners;
	Listeners listeners;
	
	void InitDebug();
	boost::shared_ptr<Tree::Dator<bool> > show_mouse_grid;
	boost::shared_ptr<Tree::Dator<bool> > show_bounds;
	
	HgeObj hge;
	
	boost::shared_ptr<Tree::Dator<bool> > debug_dude;
};
