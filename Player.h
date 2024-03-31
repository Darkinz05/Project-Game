#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAV 2
#define CAP_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_SPEED 30
class Player: public BaseObject
{
public:
	Player();
	~Player();

	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1
	};

	bool LoadImg(string path, SDL_Renderer* screen);// dung loadImg nhung co chinh sua
	void Show(SDL_Renderer* des);

	void HandleInputAction(SDL_Event e, SDL_Renderer* screen);
	void SetClip();
	void DoPlayer(Map& map_data);
	void CheckColli(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
	void CenterEntityOnMap(Map& map_data);
private:
	float x_val_;// velocity
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;
	SDL_Rect clip[10];// clip sprite
	Input input_type_;

	int frame_cur_;
	int status_; // L/R
	bool on_ground_;

	int map_x_;
	int map_y_;
};


