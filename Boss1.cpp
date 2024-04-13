#include "Boss1.h"
#include "Player.h"
#include "Bullet.h"
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}

extern int MAX_MAP_X;
extern int MAX_MAP_Y;
Boss1::Boss1()
{
	frame_cur_ = 0;
	x_pos_ = 900;
	y_pos_ = 100;
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
	rest_time = 1;
	can_shoot = 0;
	num_bullet = 3;
	active_punch = 0;
	map_x_ = 0;
	map_y_ = 0;
}
Boss1::~Boss1()
{

}
void Boss1::AdvanceState()
{
	status_ = rnd(1,2);
	global_search = 0;
}


void Boss1::Show(SDL_Renderer* des)
{
	if(pre_status_ != status_) frame_cur_ = 0;
	else frame_cur_++;
	pre_status_ = status_;
	//cout<<frame_cur_<<"\n";
	if(status_ == IDLE)
	{
		if(frame_cur_ == 4*num_sprite1[status_])
		{
			frame_cur_ = 0;
		}
		string path = "map/Boss1/Boss-idle-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
		if(frame_cur_ == 4*num_sprite1[status_] - 1)
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
	else if(status_ == SEARCH)
	{
		if(frame_cur_ == 4*num_sprite1[status_])
		{
			frame_cur_ = 0;
		}
		string path = "map/Boss1/Boss-walk-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
	}
	else if(status_ == ATTACK1 || status_ == ATTACK2)
	{
		if(frame_cur_ == 3*num_sprite1[status_]-1)
		{
			status_ = IDLE;
			rest_time = rnd(1,3);
			melee = 0;
		}
		if(frame_cur_/3 == 6) active_punch = 1;
		else if(frame_cur_/3 == 10) active_punch = 0;
//		if(frame_cur_/3 == 6 && can_shoot)
//		{
//			Bullet blet;
//			blet.LoadImg()
//		}
		string path = "map/Boss1/Boss-attack1-" + to_string(frame_cur_/3) + ".png";
		LoadImg(path, des);
	}
	int tmp = 0;

	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RendererFlip flip_type = SDL_FLIP_NONE;
	if(save_dir == RIGHT) flip_type = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(des, p_object_, NULL, &renderQuad, 0, NULL, flip_type);
}
void Boss1::DoBoss(Map& map_data, Player& player)
{
	y_val_ += BOSS_GRAV;
	if(y_val_ >= BOSS_CAP_SPEED) y_val_ = BOSS_CAP_SPEED;
	if(melee == 1) status_ = ATTACK1;

	//cout<<save_dir<<"\n";
	if(status_ == IDLE)
	{

	}
	else if(status_ == SEARCH)
	{
		int distance = (player.Box().x+player.Box().w/2) - (Box().x+Box().w/2);
		if(distance < 0) save_dir = LEFT;
		else save_dir = RIGHT;
		if (distance > 144)
		{
			x_val_ = BOSS_SPEED;
		}
		else if (distance < -144)
		{
			x_val_ = -BOSS_SPEED;
		}
		else
		{
			melee = 1;
			x_val_ = 0;
		}
	}
	else if(status_ == ATTACK1)
	{

	}
	else if(status_ == ATTACK2)
	{
		if(global_search == 0)
		{
			int distance = (player.Box().x+player.Box().w/2) - (Box().x+Box().w/2);
			if(distance < 0) save_dir = LEFT;
			else save_dir = RIGHT;
			global_search = 1;
			can_shoot = 1;
		}
	}
	CheckColli(map_data);
}
void Boss1::CheckColli(Map& map_data)
{
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;
	int height_min = Box().h<TILE_SIZE ? Box().h:TILE_SIZE;

	x_pos_ += x_val_;
	y_pos_ += y_val_;
	x1 = (Box().x) / TILE_SIZE;
	x2 = (Box().x+Box().w-1) / TILE_SIZE;

	y1 = (Box().y) / TILE_SIZE;
	y2 = (Box().y+height_min-1) / TILE_SIZE;
	if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
	{
		if(x_val_ > 0) //moving to right
		{
			if(map_data.tile[y1][x2] > 0 || map_data.tile[y2][x2] > 0)
			{
				//Box().x = x2*TILE_SIZE - width_frame_ ;
				x_pos_ = x2*TILE_SIZE - Box().w - 153;
				x_val_ = 0;
			}
		}
		else if(x_val_ < 0)
		{
			if(map_data.tile[y1][x1] > 0 || map_data.tile[y2][x1] > 0)
			{
				//Box().x = (x1+1)*TILE_SIZE;
				x_pos_ = (x1+1)*TILE_SIZE - 153;
				x_val_ = 0;
			}
		}

	}

	//check vertical
	int width_min_ = Box().w<TILE_SIZE ? Box().w:TILE_SIZE;

	x1 = (Box().x) / TILE_SIZE;// o nao cua map //trai
	x2 = (Box().x+width_min_-1) / TILE_SIZE; //phai cuar nhan vat

	y1 = (Box().y) / TILE_SIZE;
	y2 = (Box().y+Box().h-1) / TILE_SIZE;

	if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
	{
		if(y_val_ > 0)
		{
			if(map_data.tile[y2][x1] > 0 || map_data.tile[y2][x2] > 0)
			{
				//y_pos_ = y2*TILE_SIZE - height_frame_;
				y_pos_ = y2*TILE_SIZE - Box().h - 83;
				y_val_ = 0;
				on_ground_ = 1;
			}
			else
			{
				on_ground_ = 0;
			}
		}
		else if(y_val_ < 0)
		{
			if(map_data.tile[y1][x1] > 0 || map_data.tile[y1][x2] > 0)
			{
				//y_pos_ = (y1+1)*TILE_SIZE;
				y_pos_ = (y1+1)*TILE_SIZE - 83;
				y_val_ = 0;
			}
		}
	}
	//cout<<x_pos_<<" "<<y_pos_<<"\n";



	if(Box().x < 0)
	{
		x_pos_ = 0 - 153;
	}
	else if(x_pos_ + rect_.w > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - rect_.w - 1 ;// max x la diem pixel cuoi cuar map
	}
}
