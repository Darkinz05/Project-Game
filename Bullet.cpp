#include "Bullet.h"

Bullet::Bullet()
{
	frame_cur_ = 0;
	x_val_ = 20;
	y_val_ = 20;
	is_move = false;
	dir = BLEFT;
	box_x = box_y = box_w = box_h = 0;
}

Bullet::~Bullet()
{

}

void Bullet::Move(const int x_border, const int y_border)
{
	if(dir == BRIGHT)
	{
		rect_.x += x_val_;
		if(rect_.x > x_border) is_move = 0;
	}
	else if(dir == BLEFT)
	{
		rect_.x -= x_val_;
		if(rect_.x + rect_.w < 0) is_move = 0;
	}
	else if(dir == BUP)
	{
		rect_.y -= y_val_;
		if(rect_.y + rect_.h < 0) is_move = 0;
	}
	else if(dir == BDOWN)
	{
		rect_.y += y_val_;
		if(rect_.y > y_border) is_move = 0;
	}
	cout<<rect_.x<<" "<<rect_.y<<"\n";
}
