#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"


#define BOSS_GRAV 1
#define BOSS_CAP_SPEED 20
#define BOSS_SPEED 6

const int num_sprite2[]={4,10,4,8,4,9,14,8};
class Player;
class Bullet;
class Boss2: public BaseObject
{
public:
	Boss2();
	~Boss2();
	enum DIR
	{
		LEFT = 0,
		RIGHT = 1
	};
	enum STATE
	{
		IDLE = 0,
		SLAM = 1,//
		MOVE1 = 2,
		SLEEP = 3,//
		MOVE2 = 4,
		SHOOT1 = 5,//
		DEATH = 6,
		TRANS = 7
	};
	SDL_Rect Box()
	{
		//return {(int)(x_pos_ + 153), (int)(y_pos_ + 83), 81, 137};
		return {(int)(x_pos_ + 178), (int)(y_pos_ + 144), 144, 192};
	}
	SDL_Rect Punch()
	{
//		if(save_dir==0) return {(int)(x_pos_ + 12), (int)(y_pos_ + 113), 179,67};
//		return { x_pos_ + rect_.w/2 + 3,(int)(y_pos_ + 113), 179,67};
	}
	void Reset();
	void SetXY(int x, int y) {x_pos_ = x; y_pos_ = y;}
	void Show(SDL_Renderer* des);
	void ShowHealthBar(SDL_Renderer* des, TTF_Font* g_font);
	void ShowBullet(SDL_Renderer* des);
	void ShowEffect(SDL_Renderer* des);
	void AdvanceState();
	void DoBoss(Map& map_data, Player& player, SDL_Renderer* des);
	void Interaction(Player& player);
	void CheckColli(Map& map_data);
	void SetMapXY(const int map_x, const int map_y);
//private:
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;

	float x_des_;
	float y_des_;
	pair<float, float> vec;
	int reached;
	int hades;
	int num_out;

	int width_frame_;
	int height_frame_;

	int frame_cur_;
	int frame_eff_;
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
	int phase;
	int trans;

	int st_eff;
	int map_x_;
	int map_y_;
};
