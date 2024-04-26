#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

class Bullet: public BaseObject
{
public:
	Bullet();
	~Bullet();
	enum DIR
	{
		BLEFT = 0,
		BRIGHT = 1,
		BUP = 2,
		BDOWN = 3,
		BSTILL = 4
	};
	void SetForBox(int x,int y,int w,int h)
	{
		box_x = x;
		box_y = y;
		box_w = w;
		box_h = h;
	}
	SDL_Rect Box()
	{
		return {(int)x_pos_ + box_x, (int)y_pos_ + box_y, box_w, box_h};
	}
	void Move(const int x_border = SCREEN_WIDTH, const int y_border = SCREEN_HEIGHT);
	void Show(SDL_Renderer* des, int type);
	void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
//private:

	int frame_cur_;
	float x_pos_;
	float y_pos_;
	int x_val_;
	int y_val_;

	int box_x, box_y, box_w, box_h;
	bool is_move;
	int dir;
	int change;
	string name;

	int map_x_;
	int map_y_;
};
