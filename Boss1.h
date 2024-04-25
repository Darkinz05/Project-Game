#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"


#define BOSS_GRAV 1
#define BOSS_CAP_SPEED 20
#define BOSS_SPEED 6

const int num_sprite1[]={6,10,14,7,1,14,16};
class Player;
class Bullet;
class Boss1: public BaseObject
{
public:
	Boss1();
	~Boss1();
	enum DIR
	{
		LEFT = 0,
		RIGHT = 1
	};
	enum STATE
	{
		IDLE = 0,
		SEARCH = 1,
		ATTACK2 = 2,
		SPELL1 = 3,
		SPELL2 = 4,
		ATTACK1 = 5,
		DEATH = 6
	};
	SDL_Rect Box()
	{
		return {(int)(x_pos_ + 153), (int)(y_pos_ + 83), 81, 137};
	}
	SDL_Rect Punch()
	{
		if(save_dir==0) return {(int)(x_pos_ + 12), (int)(y_pos_ + 113), 179,67};
		return { x_pos_ + rect_.w/2 + 3,(int)(y_pos_ + 113), 179,67};
	}
	void Reset();
	void SetXY(int x, int y) {x_pos_ = x; y_pos_ = y;}
	void Show(SDL_Renderer* des);
	void ShowHealthBar(SDL_Renderer* des, TTF_Font* g_font);
	void ShowBullet(SDL_Renderer* des);
	void AdvanceState();
	void DoBoss(Map& map_data, Player& player, SDL_Renderer* des);
	void Interaction(Player& player);
	void CheckColli(Map& map_data);
	void SetMapXY(const int map_x, const int map_y);
//private:
	float x_val_;
	float y_val_;

	int width_frame_;
	int height_frame_;

	int frame_cur_;
	int status_;
	int pre_status_;
	bool on_ground_;
	int save_dir;
	int til_next;
	bool melee;
	int global_search;
	int rest_time;
	int active_punch;
	vector<Bullet> bullet_list;
	int can_shoot;
	int num_bullet;
	int health;
	int invincible;
	int over;
	int spell_time;
	int can_spell;
	int spell_wait;
	int can_gensp;

	int map_x_;
	int map_y_;
};
