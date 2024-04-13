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
	void Move(const int &x_border, const int &y_border);
//private:
	int x_val_;
	int y_val_;
	bool is_move;
	int dir;
};
