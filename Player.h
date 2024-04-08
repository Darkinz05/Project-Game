#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAV 1
#define CAP_SPEED 20
#define PLAYER_SPEED 8
#define PLAYER_JUMP_SPEED 20
const int num_sprite[]={4,6,4,2,5};
class Player: public BaseObject
{
public:
	Player();
	~Player();

	enum WalkType
	{
		IDLE = 0,
		WALK = 1,
		JUMPUP = 2,
		JUMPDOWN = 3,
		ATTACK = 4
	};
	enum DIR
	{
		LEFT = 0,
		RIGHT = 1
	};
	SDL_Rect Box()
	{
		return {(int)(x_pos_ + 0.4*rect_.w), (int)(y_pos_ +0.2*rect_.h), 28, 87 };
	}
	bool LoadImg(string path, SDL_Renderer* screen);// dung loadImg nhung co chinh sua
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event e);
	void SetClip();
	void DoPlayer(Map& map_data);
	void CheckColli(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
	void CenterEntityOnMap(Map& map_data);
//private:
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
	int pre_status_;
	int save_dir;
	bool on_ground_;

	int map_x_;
	int map_y_;

	int can_attack;
};


