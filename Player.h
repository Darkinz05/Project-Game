#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAV 1
#define CAP_SPEED 20
#define PLAYER_SPEED 8
#define PLAYER_JUMP_SPEED 20
#define DASH_SPEED 20
const int num_sprite[]={4,6,4,4,6,4};
class Boss1;// chatGPT
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
		ATTACK = 4,
		DASH = 5
	};
	enum DIR
	{
		LEFT = 0,
		RIGHT = 1
	};
	void Reset();
	SDL_Rect Box()
	{
		return {(int)(x_pos_ + 60), (int)(y_pos_ + 22), 30, 86 };//for 150x111
	}
	void SetXY(int x, int y) {x_pos_ = x, y_pos_ = y;}
	bool LoadImg(string path, SDL_Renderer* screen);// dung loadImg nhung co chinh sua
	void Show(SDL_Renderer* des);
	void ShowHealthBar(SDL_Renderer* des);
	void HandleInputAction(SDL_Event e);
	void SetClip();
	void DoPlayer(Map& map_data);
	void Interaction1(Boss1& boss1);
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
	int last_dir;
	bool on_ground_;

	int map_x_;
	int map_y_;

	int can_attack;
	int pro_attack;

	int dash_pos;
	int hit_wall;

	int health;
	int invincible;
	BaseObject health_bar;
};


