#include "CommonFunc.h"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
bool overlap(SDL_Rect a, SDL_Rect b)
{
	if(a.x > b.x + b.w - 1 || b.x > a.x + a.w -1) return false;
	if(a.y + a.h - 1 < b.y || b.y + b.h - 1 <a.y) return false;
	return true;
}
