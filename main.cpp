/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "Player.h"
#include "Timer.h"
#include "Button.h"
#include "Boss1.h"
#include "Boss2.h"
#undef main

using namespace std;

SDL_Window* g_window;
SDL_Renderer* g_screen;

TTF_Font* menu_font = NULL;
TTF_Font* boss_font = NULL;
TTF_Font* announce_font = NULL;
//TTF_Font* paused_font = NULL;

Mix_Music* title_music = NULL;
Mix_Music* boss1_music = NULL;
Mix_Music* boss2_music = NULL;

Mix_Chunk* dead_sfx = NULL;
Mix_Chunk* win_sfx = NULL;
Mix_Chunk* menu_sfx = NULL;
Mix_Chunk* player_hit = NULL;
Mix_Chunk* player_miss = NULL;
Mix_Chunk* player_hurt = NULL;
Mix_Chunk* boss1_attack = NULL;
Mix_Chunk* boss1_death = NULL;

int MAX_MAP_X = 20;
int MAX_MAP_Y = 14;
BaseObject g_background;
enum GAMESCENE
{
	MENU = 0,
	MAP1 = 1,
	MAP2 = 2,
	Map3 = 3,
	TUTORIAL = 4,
	SELECT = 5

};
bool Init()
{
	bool success = 1;
	int ret = SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
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

			if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
			{
				printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
				success = false;
			}
		}
	}
	return success;
}
void Close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	TTF_CloseFont( menu_font );
	TTF_CloseFont( boss_font );
	TTF_CloseFont( announce_font );
    menu_font = NULL;
    boss_font = NULL;
    announce_font = NULL;
    Mix_FreeChunk(player_hit);
    Mix_FreeMusic(title_music);
    Mix_FreeMusic(boss1_music);
    Mix_FreeMusic(boss2_music);

    Mix_Quit();
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

Player player;
GameMap game_map;


BaseObject menu_background;
BaseObject title_name;
Button play_button, tutorial_button, achievements_button;
Button home_button, sound_button, continue_button;

bool LoadMedia()
{
	menu_font = TTF_OpenFont("Corda_W01_Medium.ttf", 80);
	boss_font = TTF_OpenFont("Corda_W01_Medium.ttf", 30);
	announce_font = TTF_OpenFont("Corda_W01_Medium.ttf", 140);
	//paused_font = TTF_OpenFont("Corda_W01_Medium.ttf", 140);

	boss1_music = Mix_LoadMUS("menu/boss1_mus.ogg");
	title_music = Mix_LoadMUS("menu/title_mus.ogg");
	boss2_music = Mix_LoadMUS("menu/boss2_mus.ogg");

	dead_sfx = Mix_LoadWAV("sfx/death_scene.wav");
	win_sfx = Mix_LoadWAV("sfx/you_win.wav");
	menu_sfx = Mix_LoadWAV("sfx/menu_button.wav");
	player_hit = Mix_LoadWAV("sfx/player_hit.wav");
	player_miss = Mix_LoadWAV("sfx/player_miss.wav");
	player_hurt = Mix_LoadWAV("sfx/player_hurt.wav");
	boss1_attack = Mix_LoadWAV("sfx/boss1_attack.wav");
	boss1_death = Mix_LoadWAV("sfx/boss1_death.wav");


	menu_background.LoadImg("menu/Menu_background.png", g_screen);
	play_button.LoadTTF("Play", g_screen, menu_font, button_out);
	tutorial_button.LoadTTF("Tutorial", g_screen, menu_font, button_out);
	achievements_button.LoadTTF("Achievements", g_screen, menu_font, button_out);
	home_button.LoadImg("menu/home_button.png", g_screen);
	sound_button.LoadImg("menu/sound_button.png", g_screen);
	continue_button.LoadImg("menu/continue_button.png", g_screen);
	title_name.LoadImg("menu/Title.png", g_screen);


	return 1;
}
bool load_map1, load_select, load_map2, load_tutorial;
Button map1_button;
Button map2_button;
void LoadSelect()
{
	g_background.LoadImg("menu/Select.png", g_screen);
	g_background.SetRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
	map1_button.LoadImg("menu/Map1.png", g_screen);
	map2_button.LoadImg("menu/Map2.png", g_screen);
}

BaseObject soul;
bool soul_playing, soul_took;
void PlaySoul()
{
	soul.rect_.y-=2;
	if(soul.rect_.y<300) soul.rect_.y = 300;
}
Boss1 boss1;
void LoadMap1()
{
	g_background.LoadImg("map/Boss1/Ice_background.png",g_screen);
	g_background.SetRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	game_map.LoadMap("map/Boss1/Map1.txt");
	game_map.LoadTiles(g_screen,"map/Boss1/Tile");
	soul.LoadImg("map/soul.png", g_screen);

	soul_took = 0;
	soul_playing = 0;
}
Boss2 boss2;
void LoadMap2()
{
	g_background.LoadImg("map/Boss2/Cave_background.png",g_screen);
	g_background.SetRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT - 100);
	game_map.LoadMap("map/Boss2/Map2.txt");
	game_map.LoadTiles(g_screen,"map/Boss2/tile0");
	soul.LoadImg("map/soul.png", g_screen);

	soul_took = 0;
	soul_playing = 0;
}

BaseObject dummy;
int frame_dum, play_dum, st_dum;
void LoadTutorial()
{
	g_background.LoadImg("map/Tutorial/backtile.png", g_screen);
	game_map.LoadMap("map/Tutorial/map_tut.txt");
	game_map.LoadTiles(g_screen,"map/Tutorial/tile");
	dummy.LoadImg("map/Tutorial/dummy-0.png", g_screen);
	dummy.x_pos_ = 2300;
	dummy.y_pos_ = 492;
	frame_dum = 0;
	soul.LoadImg("map/soul.png", g_screen);

	soul.x_pos_ = 3150;
	soul.y_pos_ = 500;

	soul_took = 0;
	soul_playing = 0;
}

int scene = 0;
int volume_up = 0;
void TurnVolume()
{
	if(volume_up == 0)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
		Mix_VolumeChunk(dead_sfx,MIX_MAX_VOLUME / 2);
		Mix_VolumeChunk(menu_sfx,MIX_MAX_VOLUME / 2);
		Mix_VolumeChunk(player_hit,MIX_MAX_VOLUME / 2);
		Mix_VolumeChunk(player_miss,MIX_MAX_VOLUME / 2);
		Mix_VolumeChunk(player_hurt,MIX_MAX_VOLUME / 2);
		Mix_VolumeChunk(boss1_attack,MIX_MAX_VOLUME / 2);
		Mix_VolumeChunk(boss1_death,MIX_MAX_VOLUME);

	}
	else
	{
		Mix_VolumeMusic(0);
		Mix_VolumeChunk(dead_sfx,0);
		Mix_VolumeChunk(menu_sfx,0);
		Mix_VolumeChunk(player_hit,0);
		Mix_VolumeChunk(player_miss,0);
		Mix_VolumeChunk(player_hurt,0);
		Mix_VolumeChunk(boss1_attack,0);
		Mix_VolumeChunk(boss1_death,0);
	}
	volume_up = 1 - volume_up;
}
bool paused = 0;
void ChangeScene()
{
	int pre = scene;
	switch(scene)
	{
	case MENU:
		if(play_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			play_button.advance = 0;
			scene = SELECT;
		}
		if(tutorial_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			tutorial_button.advance = 0;
			scene = TUTORIAL;
		}
		break;
	case MAP1:
		if(home_button.GetAdvance() && paused == 0)
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			Mix_PauseMusic();
			//Mix_PlayMusic(title_music, -1);
			home_button.advance = 0;
			//scene = SELECT;
			paused = 1;
		}
		if(home_button.GetAdvance() && paused == 1)
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			home_button.advance = 0;
			Mix_PlayMusic(title_music, -1);
			scene = SELECT;
			paused = 0;
		}
		if(paused == 1 && continue_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			continue_button.advance = 0;
			Mix_ResumeMusic();
			paused = 0;
		}
		if(sound_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			sound_button.advance = 0;
			TurnVolume();
		}
		break;
	case MAP2:
		if(home_button.GetAdvance() && paused == 0)
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			Mix_PauseMusic();
			//Mix_PlayMusic(title_music, -1);
			home_button.advance = 0;
			//scene = SELECT;
			paused = 1;
		}
		if(home_button.GetAdvance() && paused == 1)
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			home_button.advance = 0;
			Mix_PlayMusic(title_music, -1);
			scene = SELECT;
			paused = 0;
		}
		if(paused == 1 && continue_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			continue_button.advance = 0;
			Mix_ResumeMusic();
			paused = 0;
		}
		if(sound_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			sound_button.advance = 0;
			TurnVolume();
		}
		break;
	case SELECT:
		if(home_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			home_button.advance = 0;
			scene = MENU;
		}
		if(sound_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			sound_button.advance = 0;
			TurnVolume();
		}
		if(map1_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			Mix_PlayMusic(boss1_music, -1);

			map1_button.advance = 0;
			scene = MAP1;
		}
		if(map2_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			Mix_PlayMusic(boss2_music, -1);

			map2_button.advance = 0;
			scene = MAP2;
		}

		break;
	case TUTORIAL:
		if(home_button.GetAdvance() && paused == 0)
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			Mix_PauseMusic();
			//Mix_PlayMusic(title_music, -1);
			home_button.advance = 0;
			//scene = SELECT;
			paused = 1;
		}
		if(home_button.GetAdvance() && paused == 1)
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			home_button.advance = 0;
			Mix_PlayMusic(title_music, -1);
			scene = MENU;
			paused = 0;
		}
		if(paused == 1 && continue_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			continue_button.advance = 0;
			Mix_ResumeMusic();
			paused = 0;
		}
		if(sound_button.GetAdvance())
		{
			Mix_PlayChannel(-1, menu_sfx, 0);
			sound_button.advance = 0;
			TurnVolume();
		}
		break;
	}

	if(pre != scene)
	{
		load_select = 0;
		load_map1 = 0;
		load_map2 = 0;
		load_tutorial = 0;
	}
}

void PausedMenu()
{
	SDL_Rect mask = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect box_;
	box_ = {350, 150, 600, 400};
	SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
	SDL_RenderFillRect(g_screen, &box_);

	box_ = {box_.x + 10, box_.y + 10, 580, 180};
	SDL_SetRenderDrawColor(g_screen, 160, 160, 160, 180);
	SDL_RenderFillRect(g_screen, &box_);

	box_ = {box_.x , box_.y +box_.h+ 10, 580, 190};
	SDL_SetRenderDrawColor(g_screen, 160, 160, 160, 180);
	SDL_RenderFillRect(g_screen, &box_);

	BaseObject paused_an;
	SDL_Color Black = {0,0,0};
	paused_an.LoadTTF("PAUSED", g_screen, announce_font, Black);
	paused_an.SetPos(400,150);
	paused_an.Render(g_screen);
	continue_button.SetRect(470, 400, 120, 80);
	continue_button.Render(g_screen);

	home_button.SetRect(700, 400, 120, 80);
	home_button.Render(g_screen);
}
BaseObject fron1, fron2;
//deathscene
int d_started, d_opa, d_opa_ann, d_frame;

int fron1_offset, fron2_offset;
int main(int argc, char *argv[])
{
	Timer time;
	if(Init() == false) return -1;
	LoadMedia();
	bool quit = 0;
	SDL_Event e;
	int next_scene = 0;

	TurnVolume();
	while(!quit)
	{

		//cout<<1<<" ";
		time.start();
		ChangeScene();// *warning*
		//event and media
//		cout<<scene<<"\n";
		switch(scene)
		{

		case MENU:
			if(Mix_PlayingMusic() == 0) Mix_PlayMusic(title_music, -1);
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					quit = true;
				}
				play_button.HandleInput(e);
				tutorial_button.HandleInput(e);
				achievements_button.HandleInput(e);
			}

			break;
		case MAP1:
			{
				if(load_map1 == 0)
				{
					MAX_MAP_X = 20;
					MAX_MAP_Y = 11;
					LoadMap1();
					load_map1 = 1;
				}
				//cout<<player.x_pos_<<"  "<<player.y_pos_<<"\n";
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					continue_button.HandleInput(e);
					home_button.HandleInput(e);
					sound_button.HandleInput(e);
					if(paused) continue;
					if(e.key.keysym.sym == SDLK_o) boss1.health = 0;
					//cout<<home_button.advance<<"\n";
					player.HandleInputAction(e);


				}
				const Uint8* keys = SDL_GetKeyboardState(NULL);
				if(keys[SDL_SCANCODE_W])
				{
					player.input_type_.jump_ = 1;
				}
				break;
			}
		case MAP2:
			{
				if(load_map2 == 0)
				{
					MAX_MAP_X = 20;
					MAX_MAP_Y = 11;
					LoadMap2();
					load_map2 = 1;
				}
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					continue_button.HandleInput(e);
					home_button.HandleInput(e);
					sound_button.HandleInput(e);
					if(paused) continue;
					if(e.key.keysym.sym == SDLK_o) boss2.health = 0;
					//cout<<home_button.advance<<"\n";
					player.HandleInputAction(e);
				}
				const Uint8* keys = SDL_GetKeyboardState(NULL);
				if(keys[SDL_SCANCODE_W])
				{
					player.input_type_.jump_ = 1;
				}
				break;

			}

		case SELECT:
			{

				if(load_select == 0)
				{
					LoadSelect();
					load_select = 1;
					player.Reset();
					boss1.Reset();
					boss2.Reset();
				}
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					map1_button.HandleInput(e);
					map2_button.HandleInput(e);
					home_button.HandleInput(e);
					sound_button.HandleInput(e);
				}
				break;
			}
		case TUTORIAL:
			{
				if(load_tutorial == 0)
				{
					MAX_MAP_X = 58;
					MAX_MAP_Y = 16;
					LoadTutorial();
					load_tutorial = 1;
					player.Reset();
				}
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					continue_button.HandleInput(e);
					home_button.HandleInput(e);
					sound_button.HandleInput(e);
					if(paused) continue;
					//cout<<home_button.advance<<"\n";
					player.HandleInputAction(e);
				}
				const Uint8* keys = SDL_GetKeyboardState(NULL);
				if(keys[SDL_SCANCODE_W])
				{
					player.input_type_.jump_ = 1;
				}
			}
		}

		//logic

		//render
		SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
		SDL_RenderClear(g_screen);
		switch(scene)
		{
		case MENU:
			{
				menu_background.SetRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				menu_background.Render(g_screen);


				SDL_SetRenderDrawColor(g_screen, 160, 160, 160, 180);
//				SDL_Rect box_ = {SCREEN_WIDTH/2 - 300, 250, 600, 400};
//				SDL_RenderFillRect(g_screen, &box_);


				title_name.SetPos((SCREEN_WIDTH-title_name.rect_.w)/2,5);
				title_name.Render(g_screen);
				//button

				play_button.SetPos(SCREEN_WIDTH/2 - play_button.GetRect().w/2, 260);
				SDL_Rect box_ = play_button.rect_;box_.x -= 16; box_.w += 32; box_.y -= 8; box_.h += 16;
				SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
				SDL_RenderFillRect(g_screen, &box_);
				box_ = play_button.rect_;box_.x -= 10; box_.w += 20;
				SDL_SetRenderDrawColor(g_screen, 160, 160, 160, 180);
				SDL_RenderFillRect(g_screen, &box_);
				play_button.Show(g_screen, menu_font, 1, "Play");

				tutorial_button.SetPos(SCREEN_WIDTH/2 - tutorial_button.GetRect().w/2, 260 + play_button.rect_.h + 20);
				box_ = tutorial_button.rect_;box_.x -= 16; box_.w += 32; box_.y -= 8; box_.h += 16;
				SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
				SDL_RenderFillRect(g_screen, &box_);
				box_ = tutorial_button.rect_;box_.x -= 10; box_.w += 20;
				SDL_SetRenderDrawColor(g_screen, 160, 160, 160, 180);
				SDL_RenderFillRect(g_screen, &box_);
				tutorial_button.Show(g_screen, menu_font, 1, "Tutorial");

//				achievements_button.SetPos(SCREEN_WIDTH/2 - achievements_button.GetRect().w/2, tutorial_button.rect_.y + tutorial_button.rect_.h + 5);
//				box_ = achievements_button.rect_;box_.x -= 10; box_.w += 20;
//				SDL_RenderFillRect(g_screen, &box_);
//				achievements_button.Show(g_screen, menu_font, 1, "Achievements");
				break;
			}

		case MAP1:
			{
				g_background.Render(g_screen);
				game_map.DrawMap(g_screen);
				Map map_data = game_map.GetMap();
				if(boss1.status_ == Boss1::DEATH)
				{
					if(soul_playing == 0)
					{
						soul.SetPos(boss1.rect_.x+170, 500);
						soul_playing = 1;
					}
					PlaySoul();
					if(soul.rect_.y == 300 && overlap(player.Box(), soul.rect_)) soul_took = 1;
					if(soul_took == 0) soul.Render(g_screen);
				}

				//tes.Render(g_screen);
				boss1.SetMapXY(map_data.start_x_, map_data.start_y_);
				if(!paused) boss1.Interaction(player);
				if(!paused) boss1.DoBoss(map_data, player, g_screen);
				boss1.Show(g_screen);

				player.SetMapXY(map_data.start_x_, map_data.start_y_);
				if(!paused) player.Interaction1(boss1);
				if(!paused) player.DoPlayer(map_data);
				player.Show(g_screen);

				boss1.ShowHealthBar(g_screen, boss_font);
				player.ShowHealthBar(g_screen);

				game_map.SetMap(map_data);
				//game_map.DrawMap(g_screen);

				if(!paused)
				{
					home_button.SetPos(290, 19);
					home_button.Show(g_screen,NULL,2,"menu/home_button");

					sound_button.SetPos(370,19);
					sound_button.Show(g_screen,NULL,2,"menu/sound_button");
				}
				else
				{
					PausedMenu();

				}
				//cout<<continue_button.is_hovered<<"\n";
				break;
			}
		case MAP2:
			{
				g_background.Render(g_screen);
				Map map_data = game_map.GetMap();

				boss2.SetMapXY(map_data.start_x_, map_data.start_y_);
				if(!paused) boss2.Interaction(player);
				if(!paused) boss2.DoBoss(map_data, player, g_screen);
				boss2.Show(g_screen);
				game_map.DrawMap(g_screen);


				if(boss2.status_ == Boss2::DEATH && boss2.frame_cur_/4 >= 13)
				{
					if(soul_playing == 0)
					{
						soul.SetPos(boss2.rect_.x+200, 530);
						soul_playing = 1;
					}
					PlaySoul();
					if(soul.rect_.y == 300 && overlap(player.Box(), soul.rect_)) soul_took = 1;
					if(soul_took == 0) soul.Render(g_screen);
				}




				player.SetMapXY(map_data.start_x_, map_data.start_y_);

				if(!paused) player.Interaction2(boss2);
				if(!paused) player.DoPlayer(map_data);
				player.Show(g_screen);

				boss2.ShowHealthBar(g_screen, boss_font);
				player.ShowHealthBar(g_screen);
				game_map.SetMap(map_data);

				if(!paused)
				{
					home_button.SetPos(290, 19);
					home_button.Show(g_screen,NULL,2,"menu/home_button");

					sound_button.SetPos(370,19);
					sound_button.Show(g_screen,NULL,2,"menu/sound_button");
				}
				else
				{
					PausedMenu();

				}
				break;
			}
		case SELECT:
			{
				g_background.Render(g_screen);
				map1_button.SetPos(160, 240);
				map1_button.Show(g_screen,NULL,2,"menu/Map1");

				map2_button.SetPos(420, 80);
				map2_button.Show(g_screen,NULL,2,"menu/Map2");

				home_button.SetPos(20, 20);
				home_button.Show(g_screen,NULL,2,"menu/home_button");

				sound_button.SetPos(100, 20);
				sound_button.Show(g_screen,NULL,2,"menu/sound_button");
				break;
			}
		case TUTORIAL:
			{
				//g_background.Render(g_screen);

				Map map_data = game_map.GetMap();
				SDL_Rect clip = {map_data.start_x_, map_data.start_y_,SCREEN_WIDTH,SCREEN_HEIGHT};
				SDL_Rect renderQuad = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
				SDL_RenderCopy(g_screen, g_background.p_object_, &clip, &renderQuad);

				dummy.SetMapXY(map_data.start_x_, map_data.start_y_);

				if(player.active_attack && overlap(player.AttackBox(), {dummy.x_pos_, dummy.y_pos_, dummy.rect_.w, dummy.rect_.h}) && play_dum == 0) st_dum = 1;
				if(player.active_attack && !overlap(player.AttackBox(), {dummy.x_pos_, dummy.y_pos_, dummy.rect_.w, dummy.rect_.h})) if(Mix_Playing(5) == 0) Mix_PlayChannel(5, player_miss, 0);
				if(st_dum == 1)
				{
					play_dum = 1;
					st_dum = 0;
					frame_dum = 0;
					if(Mix_Playing(5) == 0) Mix_PlayChannel(5, player_hit, 0);
				}
				if(play_dum)
				{
					frame_dum++;
				}

				string paht = "map/Tutorial/dummy-" + to_string(frame_dum/4) + ".png";
				dummy.LoadImg(paht, g_screen);
				dummy.Show(g_screen);
				if(frame_dum == 4*4 - 1) play_dum = 0;

				soul.SetMapXY(map_data.start_x_, map_data.start_y_);
				if(overlap(player.Box(), {soul.x_pos_, soul.y_pos_, soul.rect_.w, soul.rect_.h})) soul_took = 1;
				if(soul_took == 0) soul.Show(g_screen);



				game_map.DrawMap(g_screen);


				player.SetMapXY(map_data.start_x_, map_data.start_y_);
				if(!paused) player.DoPlayer(map_data);
				player.Show(g_screen);
				player.ShowHealthBar(g_screen);
				game_map.SetMap(map_data);

				if(!paused)
				{
					home_button.SetPos(290, 19);
					home_button.Show(g_screen,NULL,2,"menu/home_button");

					sound_button.SetPos(370,19);
					sound_button.Show(g_screen,NULL,2,"menu/sound_button");
				}
				else
				{
					PausedMenu();
				}
				break;
			}
		}

		if(scene>=1&&scene<=4)//death scene
		{
			if(player.status_ == Player::DEATH)
			{
				if(d_started == 0)
				{
					Mix_HaltMusic();
					Mix_PlayChannel(-1, dead_sfx, 0);
					d_frame = 0;
					d_opa = 0;
					d_opa_ann = 0;
					d_started = 1;
				}
				d_frame++;
				d_opa+=4;
				if(d_opa>255) d_opa = 255;
				SDL_SetRenderDrawColor(g_screen, 0, 0, 0, d_opa);
				SDL_Rect box = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
				SDL_RenderFillRect(g_screen, &box);

				if(d_frame >= 80)
				{
					d_opa_ann+=6;
					if(d_opa_ann>255) d_opa_ann = 255;
				}
				BaseObject dead_an;
				SDL_Color Red = {104,39,32};
				dead_an.LoadTTF("YOU DIED", g_screen, announce_font, Red);
				dead_an.SetPos(350,200);
				SDL_SetTextureAlphaMod(dead_an.p_object_, d_opa_ann);
				dead_an.Render(g_screen);

				if(d_frame == 200)
				{
					Mix_PlayMusic(title_music, -1);
					scene = SELECT;
					d_started = 0;
				}
			}
			else if(soul_took)
			{
				if(d_started == 0)
				{
					Mix_HaltMusic();
					Mix_PlayChannel(-1, win_sfx, 0);
					d_frame = 0;
					d_opa = 0;
					d_opa_ann = 0;
					d_started = 1;
				}
				d_frame++;
				d_opa+=4;
				if(d_opa>255) d_opa = 255;
				SDL_SetRenderDrawColor(g_screen, 0, 0, 0, d_opa);
				SDL_Rect box = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
				SDL_RenderFillRect(g_screen, &box);
//				if(d_frame == 100)
//				{
//					Mix_PlayMusic(title_music, -1);
//					scene = SELECT;
//					d_started = 0;
//				}
				if(d_frame >= 80)
				{
					d_opa_ann+=6;
					if(d_opa_ann>255) d_opa_ann = 255;
				}
				BaseObject dead_an;
				SDL_Color Yellow = {244,255,0};
				dead_an.LoadTTF("YOU WIN!", g_screen, announce_font, Yellow);
				dead_an.SetPos(350,200);
				SDL_SetTextureAlphaMod(dead_an.p_object_, d_opa_ann);
				dead_an.Render(g_screen);

				if(d_frame == 200)
				{
					Mix_HaltChannel(-1);
					Mix_PlayMusic(title_music, -1);
					scene = SELECT;
					d_started = 0;
				}
			}
		}

		SDL_RenderPresent(g_screen);
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
