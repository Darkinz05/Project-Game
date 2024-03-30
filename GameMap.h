#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 10
class TileMat: public BaseObject
{
public:
	TileMat(){;}
	~TileMat(){;}

};


class GameMap
{
public:
	GameMap(){;}
	~GameMap(){;}

	void LoadMap(char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map GetMap() const {return game_map_;}

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];

};
