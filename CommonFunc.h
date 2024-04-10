#pragma once

#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

#define SCREEN_WIDTH 	1280
#define SCREEN_HEIGHT	704
#define GAME_NAME 		"PROJECT-GAME"

const int keyR = 54;
const int keyG = 136;
const int keyB = 153;

#define TILE_SIZE 64
#define MAX_MAP_X 20
#define MAX_MAP_Y 14

const SDL_Color button_out = {0,0,0,255};
const SDL_Color button_in = {255,255,211,255};
const int fps = 40;

struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
	int attack_;
	int dash_;
};
struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	string file_name_;

};
#endif // COMMON_FUNC_H

