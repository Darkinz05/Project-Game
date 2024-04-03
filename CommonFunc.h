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
#define SCREEN_HEIGHT	640
#define GAME_NAME 		"PROJECT-GAME"

const int keyR = 144;
const int keyG = 132;
const int keyB = 146;

#define TILE_SIZE 80
#define MAX_MAP_X 400
#define MAX_MAP_Y 13

const int fps = 60;
struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};
struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;

};
#endif // COMMON_FUNC_H
