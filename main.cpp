/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "Player.h"

#undef main

using namespace std;

SDL_Window* g_window;
SDL_Renderer* g_screen;
BaseObject g_background;

bool Init()
{
	bool success = 1;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if(ret < 0) return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

	g_window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if(g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags)&&imgFlags))
			{
				success = 0;
			}
		}
	}
	return success;
}

bool LoadBackground()
{
	bool ret = g_background.LoadImg("2493466.png",g_screen);
	return ret;
}

void Close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();


}
int main(int argc, char *argv[])
{
	if(Init() == false) return -1;
	if(LoadBackground() == false) return -1;

	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);
	cout<<1;
	Player player;
	player.LoadImg("Character/knight_right.png", g_screen);
	player.SetClip();
	bool quit = 0;
	SDL_Event e;
	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}

			player.HandleInputAction(e, g_screen);

		}

		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen);

		game_map.DrawMap(g_screen);
		Map map_data = game_map.GetMap();

		player.DoPlayer(map_data);
		player.Show(g_screen);

		SDL_RenderPresent(g_screen);
	}

	Close();

	return 0;
}
