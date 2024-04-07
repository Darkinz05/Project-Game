/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "Player.h"
#include "Timer.h"
#include "Button.h"
#undef main

using namespace std;

SDL_Window* g_window;
SDL_Renderer* g_screen;
BaseObject g_background;
enum GAMESCENE
{
	MENU = 0,
	SUB1 = 1,
	TEST = 2
};
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
		SDL_SetRenderDrawBlendMode(g_screen, SDL_BLENDMODE_BLEND);
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

			if(TTF_Init() == -1)
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

Player player;
GameMap game_map;

BaseObject menu_background;
Button play_button;

TTF_Font* g_font = NULL;
bool LoadMedia()
{
	g_font = TTF_OpenFont("Corda_W01_Medium.ttf", 80);
	if(LoadBackground() == false) return 0;

	//game_map.LoadMap("map/map01.dat");
	game_map.LoadMap("map/map11.txt");
	game_map.LoadTiles(g_screen);

	player.LoadImg("Character/knight_right.png", g_screen);
	player.SetClip();// 8

	menu_background.LoadImg("menu/Menu_background.png", g_screen);
	play_button.LoadTTF("Play", g_screen, g_font, button_out);
	return 1;
}

int scene = 0;
void ChangeScene()
{
	switch(scene)
	{
	case MENU:
		if(play_button.GetAdvance()) scene = SUB1;
		break;
	case SUB1:

		break;
	}
}
int main(int argc, char *argv[])
{
	Timer time;
	if(Init() == false) return -1;
	LoadMedia();
	bool quit = 0;
	SDL_Event e;
	int next_scene = 0;
	while(!quit)
	{
		//cout<<1<<" ";
		time.start();
		//event
		switch(scene)
		{
		case MENU:
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					quit = true;
				}
				play_button.HandleInput(e);
			}
			break;
		case SUB1:
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					quit = true;
				}
				player.HandleInputAction(e);
			}
			break;
		}

		//logic
		switch(scene)
		{
		case MENU:

			break;
		case SUB1:
			break;
		}

		ChangeScene();
		//render
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);
		switch(scene)
		{
		case MENU:
			{
				menu_background.SetRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				menu_background.Render(g_screen);

				SDL_SetRenderDrawColor(g_screen, 160, 160, 160, 180);
				SDL_Rect box_ = {SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 250, 400, 500};
				SDL_RenderFillRect(g_screen, &box_);

				play_button.SetPos(SCREEN_WIDTH/2 - play_button.GetRect().w/2, 110);
				play_button.Show(g_screen, g_font, 1, "Play");

				SDL_RenderPresent(g_screen);
				break;
			}

		case SUB1:
			{
				g_background.Render(g_screen);

				game_map.DrawMap(g_screen);
				Map map_data = game_map.GetMap();
				//tes.Render(g_screen);
				player.SetMapXY(map_data.start_x_, map_data.start_y_);
				player.DoPlayer(map_data);
				player.Show(g_screen);

				game_map.SetMap(map_data);
				game_map.DrawMap(g_screen);
				SDL_RenderPresent(g_screen);
				break;
			}

		}


		int pass_tick = time.getTicks();

		int time_per_frame = 1000/fps;//ms

		if(pass_tick < time_per_frame)
		{
			SDL_Delay(time_per_frame - pass_tick);
		}
	}

	Close();

	return 0;
}
