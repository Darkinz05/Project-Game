#include "CommonFunc.h"

bool overlap(SDL_Rect a, SDL_Rect b)
{
	if(a.x > b.x + b.w - 1 || b.x > a.x + a.w -1) return false;
	if(a.y + a.h - 1 < b.y || b.y + b.h - 1 <a.y) return false;
	return true;
}
