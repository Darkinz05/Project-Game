#pragma once

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y, const int& w, const int& h)
	{
		rect_.x=x;
		rect_.y=y;
		rect_.w=w;
		rect_.h=h;
	}
	void SetPos(const int& x, const int& y)
	{
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const {return rect_;}
	SDL_Texture* GetObject() const {return p_object_;}

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);// dung loadImg nhung co chinh sua trong cac lop con
	virtual void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
	virtual void Show(SDL_Renderer* des);
	bool LoadTTF(std::string text, SDL_Renderer* screen, TTF_Font* font, SDL_Color text_color);
	void Render(SDL_Renderer* des,const SDL_Rect* clip = NULL);
	void Free();

//protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
	float x_pos_;
	float y_pos_;

	int map_x_;
	int map_y_;
};
