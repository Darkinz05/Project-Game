#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

class Button: public BaseObject
{
public:
	Button();
	~Button();
	void HandleInput(SDL_Event event);
	void Show(SDL_Renderer* des);
	bool GetAdvance() {return advance;}
	bool SetAdvance() {advance = 0;}
private:
	bool is_hovered;
	bool press = 0;
	bool isInBound(int x, int y)
	{
		if(x<rect_.x) return false;
		if(x>rect_.x+rect_.w) return false;
		if(y<rect_.y) return false;
		if(y>rect_.y+rect_.h) return false;
		return true;
	}
	bool advance;
};
