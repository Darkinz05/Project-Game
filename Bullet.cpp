#include "Bullet.h"

Bullet::Bullet()
{
	frame_cur_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	is_move = false;
	dir = BLEFT;
	box_x = box_y = box_w = box_h = 0;

	map_x_ = 0;
	map_y_ = 0;
}

Bullet::~Bullet()
{

}

void Bullet::Move(const int x_border, const int y_border)
{
	if(dir == BRIGHT)
	{
		x_pos_ += x_val_;
		if(x_pos_ > x_border) is_move = 0;
	}
	else if(dir == BLEFT)
	{
		x_pos_ -= x_val_;
		if(x_pos_ + Box().w < 0) is_move = 0;
	}
	else if(dir == BUP)
	{
		y_pos_ -= y_val_;
		if(y_pos_ + Box().h < 0) is_move = 0;
	}
	else if(dir == BDOWN)
	{
		y_pos_ += y_val_;
		if(y_pos_ > y_border) is_move = 0;
	}
	//cout<<x_pos_<<" "<<rect_.y<<"\n";
}

void Bullet::Show(SDL_Renderer* des, int type)
{
	frame_cur_++;
	if(frame_cur_ == 5*10)
	{
		frame_cur_ = 0;
	}
	string path = "map/Boss1/Boss-bullet-" + to_string(frame_cur_/5) + ".png";
	if(type == 2) path = "map/Boss1/Boss-bullet2-" + to_string(frame_cur_/5) + ".png";
	LoadImg(path, des);
	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;
	SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RendererFlip flip_type = SDL_FLIP_NONE;
	if(dir == BLEFT) flip_type = SDL_FLIP_HORIZONTAL;
	if(dir == BDOWN) flip_type = SDL_FLIP_VERTICAL;
	SDL_RenderCopyEx(des, p_object_, NULL, &renderQuad, 0, NULL, flip_type);
}
