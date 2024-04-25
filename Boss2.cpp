#include "Boss2.h"
#include "Player.h"
#include "Bullet.h"


extern int MAX_MAP_X;
extern int MAX_MAP_Y;
extern Mix_Chunk* player_hit;
extern Mix_Chunk* player_miss;
extern Mix_Chunk* boss1_attack;
extern Mix_Chunk* boss1_death;

extern bool paused;
Boss2::Boss2()
{
	frame_cur_ = 0;
	frame_eff_ = 0;
	x_pos_ = 700;
	y_pos_ = 112;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = 0;
	pre_status_ = -2;
	save_dir = LEFT;
	til_next = 0;
	melee = 0;
	global_search = 0;
	rest_time = 2;
	can_shoot = 0;
	num_bullet = 3;
	active_punch = 0;
	health = 30;
	invincible = 0;
	over = 0;
	spell_time = 0;
	spell_wait = 0;
	can_gensp = 1;
	st_eff = 0;
	map_x_ = 0;
	map_y_ = 0;
}
Boss2::~Boss2()
{

}
void Boss2::Reset()
{
	Boss2 tmp;
	*this = tmp;
}

void Boss2::AdvanceState()
{
	status_ = rnd(1,1);
	spell_time = 0;
	global_search = 0;
}

void Boss2::Show(SDL_Renderer* des)
{

	if(pre_status_ != status_) frame_cur_ = 0;
	else if(paused == 0 )frame_cur_++;
	pre_status_ = status_;

	if(status_ == IDLE)
	{
		if(frame_cur_ == 4*num_sprite2[status_])
		{
			frame_cur_ = 0;
		}
		string path = "map/Boss2/Boss-idle-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
		if(frame_cur_ == 4*num_sprite2[status_] - 1)
		{
			til_next++;
			if(til_next == rest_time)
			{
				til_next = 0;
				//cout<<1<<"\n";
				AdvanceState();
			}
		}

	}
	else if(status_ == DEATH)
	{
		if(frame_cur_ == 4*num_sprite2[status_])
		{
			frame_cur_ = 4*num_sprite2[status_]-1;
		}
		string path = "map/Boss2/Boss-death-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
	}
	else if(status_ == SLAM)
	{
		if(frame_cur_/5 == 13)
		{
			status_ = IDLE;
			rest_time = rnd(2,3);
			melee = 0;
			//frame_cur_ = 5*num_sprite2[status_]-1;
		}

		if(frame_cur_/5 == 4)
		{
			st_eff = 1, frame_eff_ = 0;

		}
		string path = "map/Boss2/Boss-slam-" + to_string(min(9,frame_cur_/5)) + ".png";
		LoadImg(path, des);
	}
	ShowEffect(des);
	int tmp = 0;

	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RendererFlip flip_type = SDL_FLIP_NONE;
	if(save_dir == RIGHT) flip_type = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(des, p_object_, NULL, &renderQuad, 0, NULL, flip_type);

//	ShowBullet(des);
}
void Boss2::ShowEffect(SDL_Renderer* des)
{
	if(status_ == SLAM)
	{
		if(st_eff == 0) return;
		if(paused == 0) frame_eff_++;
		//if(st_eff) frame_eff_ = 0;
		if(frame_eff_ == 2*10) frame_eff_ = 2*10-1;
		//cout<<frame_eff_<<" ";
		BaseObject aura;
		string path = "map/Boss2/Boss-aura-" + to_string(frame_eff_/2) + ".png";
		//cout<<frame_eff_/2<<" ";
		aura.LoadImg(path, des);
		SDL_Rect renderQuad = {rect_.x + 60, rect_.y + 60, aura.rect_.w, aura.rect_.h};
		SDL_RendererFlip flip_type = SDL_FLIP_NONE;
		SDL_RenderCopyEx(des, aura.p_object_, NULL, &renderQuad, 0, NULL, flip_type);
	}
	else st_eff = 0, frame_eff_ = 0;
}
void Boss2::ShowHealthBar(SDL_Renderer* des, TTF_Font* g_font)
{
	BaseObject name;
	SDL_Color White = {255,255,255};
	name.LoadTTF("Boss: Stone Golem", des, g_font, White);
	name.SetPos(SCREEN_WIDTH - name.rect_.w - 20, 5);
	name.Render(des);

	SDL_SetRenderDrawColor(des, 0,0,0,255);
	SDL_Rect back_box = {SCREEN_WIDTH/2 + 14, name.rect_.y + name.rect_.h + 1, 616, 50};
	SDL_RenderFillRect(des, &back_box);

	SDL_SetRenderDrawColor(des, 255,255,255,255);
	int hlost = (30 - health)*600/30; //cout<<hlost;
	SDL_Rect mid_box = {back_box.x + 8 + hlost, back_box.y + 8, 600 - hlost, 34};
	SDL_RenderFillRect(des, &mid_box);

	SDL_SetRenderDrawColor(des, 255,0,0,255);

	SDL_Rect front_box = {back_box.x + 8 + hlost, back_box.y + 8, 600 - hlost, 34};
	SDL_RenderFillRect(des, &front_box);
}
void Boss2::Interaction(Player& player)
{
	//cout<<health<<"\n";
	if(invincible == 0)
	{
		bool get_hit = 0;
		if(player.active_attack==1)
		{
			if(overlap(player.AttackBox(), Box())) get_hit = 1;
		}

		if(get_hit == 1 && health > 0)
		{
			health--;
			invincible = 20;
		}
		if(health == 0 && status_ != DEATH) Mix_PlayChannel(-1, boss1_death, 0);
		if(get_hit == 1 && status_ != DEATH) Mix_PlayChannel(-1, player_hit, 0);
		if(get_hit == 0 && player.active_attack == 1)
		{
			if(Mix_Playing(5) == 0) Mix_PlayChannel(5, player_miss, 0);
		}
	}
	else
	{
		invincible--;
	}
}
void Boss2::DoBoss(Map& map_data, Player& player, SDL_Renderer* des)
{
	if(health <= 0) status_ = DEATH;
	if(player.status_ == Player::DEATH) status_ = IDLE;
	x_val_ = 0;
	y_val_ = 0;
	if(status_ == IDLE)
	{
		if(save_dir == LEFT) x_val_ = -BOSS_SPEED;
		else x_val_ = BOSS_SPEED;
	}
	else if(status_ == DEATH)
	{
		x_val_ = 0;
		y_val_ = 0;
	}
	else if(status_ == SLAM)
	{
		if(save_dir == LEFT) x_val_ = -BOSS_SPEED;
		else x_val_ = BOSS_SPEED;
	}
	CheckColli(map_data);
}
void Boss2::CheckColli(Map& map_data)
{
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if(Box().x < 0)
	{
		x_pos_ = 0 - 178;
		save_dir = RIGHT;
	}
	else if(x_pos_ + rect_.w - 100 > map_data.max_x_)
	{
		save_dir = LEFT;
		x_pos_ = map_data.max_x_ - rect_.w + 99 ;// max x la diem pixel cuoi cuar map
	}
}
void Boss2::SetMapXY(const int map_x, const int map_y)
{
	map_x_ = map_x; map_y_ = map_y;
	for(Bullet bullet: bullet_list)
	{
		bullet.SetMapXY(map_x, map_y);
	}
}
