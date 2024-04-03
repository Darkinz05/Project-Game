#include "GameMap.h"

void GameMap::LoadMap(char* name)
{
	std::ifstream fin(name);

	if(!fin)
	{
		std::cout<<"can't load map";
		return;
	}

	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;
	for(int i=0; i<MAX_MAP_Y; ++i)
	{
		for(int j=0; j<MAX_MAP_X; ++j)
		{
			fin>>game_map_.tile[i][j];
			int val = game_map_.tile[i][j];
			//cout<<i<<" "<<j<<" "<<val<<"\n";
			if(val > 0)
			{
				if(j > game_map_.max_x_) game_map_.max_x_=j;
				if(i > game_map_.max_y_) game_map_.max_y_=i;

			}
		}
		//cout<<"\n";
	}

	game_map_.max_x_ = (game_map_.max_x_+1)*TILE_SIZE;
	game_map_.max_y_ = (game_map_.max_y_+1)*TILE_SIZE;// xa nhat cua map

	game_map_.start_x_ = 0;
	game_map_.start_y_ = 0;
	game_map_.file_name_ = name;
	fin.close();
}

void GameMap::LoadTiles(SDL_Renderer* screen)// load cho tile
{
	std::string name;
	for(int i=0; i < MAX_TILES; ++i)
	{
		//cout<<i<<" ";
		name = "map/Pane.png";
		std::ifstream fin(name);
		if(!fin)
		{
			continue;
		}
		fin.close();
		tile_mat[i].LoadImg(name, screen);

	}
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1=0, x2=0;
	int y1=0, y2=0;

	int map_x = 0;
	int map_y = 0;
	map_x = game_map_.start_x_/TILE_SIZE;
	map_y = game_map_.start_y_/TILE_SIZE;

	x1 = (game_map_.start_x_ % TILE_SIZE)*-1;// render o ben trai o start_x_
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0:TILE_SIZE);//render phan be phai camera

	y1 = (game_map_.start_y_ % TILE_SIZE)*-1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0:TILE_SIZE);//tuong tu

	//render
	// i,j: start pos pixel cua 1 o
	// mapx,mapy: index 1 o
	for(int i=y1; i<y2; i+=TILE_SIZE)
	{
		map_x = game_map_.start_x_/TILE_SIZE;//index 1 o trong map
		for(int j=x1; j<x2; j+=TILE_SIZE)// start pixel o tiep theo
		{
			int val = game_map_.tile[map_y][map_x];
			if(val)
			{
				tile_mat[val].SetRect(j,i,TILE_SIZE,TILE_SIZE);

				tile_mat[val].Render(screen);

			}
			map_x++;

		}
		map_y++;
	}

}
