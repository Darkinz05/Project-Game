#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAV 0.8
#define CAP_SPEED 7
#define PLAYER_SPEED 3
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
};


