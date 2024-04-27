#include "Boss1.h"
#include "Player.h"
#include "Bullet.h"


extern int MAX_MAP_X;
extern int MAX_MAP_Y;
extern Mix_Chunk* player_hit;
extern Mix_Chunk* player_miss;
extern Mix_Chunk* boss1_attack;
extern Mix_Chunk* boss1_death;

extern bool paused;
Boss1::Boss1()
{
	frame_cur_ = 0;
	x_pos_ = 700;
	y_pos_ = 400;
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
	rest_time = 3;
	can_shoot = 0;
	num_bullet = 3;
	active_punch = 0;
	health = 20;
	invincible = 0;
	over = 0;
	spell_time = 0;
	spell_wait = 0;
	can_gensp = 1;
	map_x_ = 0;
	map_y_ = 0;
}
Boss1::~Boss1()
{

}
void Boss1::Reset()
{
	Boss1 tmp;
	*this = tmp;
}
void Boss1::AdvanceState()
{
	status_ = rnd(1,3);
	spell_time = 0;
	global_search = 0;
}


void Boss1::Show(SDL_Renderer* des)
{
	if(pre_status_ != status_) frame_cur_ = 0;
	else if(paused == 0) frame_cur_++;
	pre_status_ = status_;
	//cout<<status_<<" "<<x_pos_<<" "<<y_pos_<<"\n";
	//cout<<frame_cur_<<"\n";
//	cout<<status_<<"\n";
	if(status_ >= 2 && status_ <= 5 && frame_cur_ == 0)
	{
		Mix_PlayChannel(-1, boss1_attack, 0);
	}
	if(status_ == IDLE)
	{
		if(frame_cur_ == 3*num_sprite1[status_])
		{
			frame_cur_ = 0;
		}
		string path = "map/Boss1/Boss-idle-" + to_string(frame_cur_/3) + ".png";
		LoadImg(path, des);
		if(frame_cur_ == 3*num_sprite1[status_] - 1)
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
			rest_time = rnd(2,3);
			melee = 0;
			//cout<<22323<<"\n";
		}
		if(frame_cur_/3 == 8) active_punch = 1;
		else if(frame_cur_/3 == 10) active_punch = 0;
		if(frame_cur_/3 == 8 && can_shoot)
		{
			Bullet blet;
			blet.LoadImg("map/Boss1/Boss-bullet-0.png", des);
			blet.x_val_ = rnd(10,20);
			if(save_dir == LEFT)
			{
				blet.dir = Bullet::BLEFT;
				blet.SetForBox(66,69,179,65);
				//SDL_Rect tBox = blet.Box(66, 69, 179, 65);
				//blet.SetPos(rect_.x, rect_.y + 50);
				blet.x_pos_ = rect_.x - blet.Box().w - 10;
				blet.y_pos_ = rect_.y + 50;
			}
			else if(save_dir == RIGHT)
			{
				blet.dir = Bullet::BRIGHT;
				blet.SetForBox(66,69,179,65);
				//SDL_Rect tBox = blet.Box(66, 69, 179, 65);
				//blet.SetPos(rect_.x, rect_.y + 50);
				blet.x_pos_ = rect_.x + rect_.w - 100;
				blet.y_pos_ = rect_.y + 50;
			}

			blet.is_move = 1;
			bullet_list.push_back(blet);
			can_shoot = 0;

		}
		string path = "map/Boss1/Boss-attack1-" + to_string(frame_cur_/3) + ".png";
		LoadImg(path, des);
	}
	else if(status_ == DEATH)
	{
		if(frame_cur_ == 4*num_sprite1[status_])
		{
			frame_cur_ = 4*num_sprite1[status_]-1;
		}
		string path = "map/Boss1/Boss-death-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
	}
	else if(status_ == SPELL1)
	{
		if(frame_cur_ == 4*num_sprite1[status_])
		{
			frame_cur_ = 4*num_sprite1[status_]-1;
			spell_time++;
		}
		string path = "map/Boss1/Boss-spell1-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
		if(spell_time == 30)
		{
			status_ = IDLE;
			rest_time = rnd(2,3);
		}
		if(frame_cur_/4 == 4 && can_spell)
		{
			int dif = 50;
			for(int i=1; i<=3; ++i)
			{
				Bullet blet;
				blet.LoadImg("map/Boss1/Boss-bullet2-0.png", des);
				blet.y_val_ = rnd(20,20);

					blet.dir = Bullet::BUP;
					blet.SetForBox(34,40,30,75);
					//SDL_Rect tBox = blet.Box(66, 69, 179, 65);
					//blet.SetPos(rect_.x, rect_.y + 50);
					blet.x_pos_ = rect_.x + dif*(i-1) + 100;
					blet.y_pos_ = rect_.y - 100;


				blet.is_move = 1;
				bullet_list.push_back(blet);
				can_spell = 0;
			}
		}
	}
	int tmp = 0;

	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RendererFlip flip_type = SDL_FLIP_NONE;
	if(save_dir == RIGHT) flip_type = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(des, p_object_, NULL, &renderQuad, 0, NULL, flip_type);

	ShowBullet(des);
}

void Boss1::ShowBullet(SDL_Renderer* des)
{
	for(int i=(int)bullet_list.size()-1; i>=0; --i)
	{
		Bullet *x = &bullet_list[i];

		if(x->is_move)
		{
			int type = 0;
			if(x->dir == Bullet::BLEFT || x->dir == Bullet::BRIGHT) type = 0;
			else type = 2;
			if(paused ==0 ) x->Move();
			x->Show(des, type);

		}
		else
		{
			if(x->dir == Bullet::BUP) spell_wait++;
			if(x->dir == Bullet::BDOWN) can_gensp = 1;
			bullet_list.erase(bullet_list.begin() + i);
		}
	}
}
void Boss1::ShowHealthBar(SDL_Renderer* des, TTF_Font* g_font)
{
	BaseObject name;
	SDL_Color Black = {0,0,0};
	name.LoadTTF("Boss: Frost Guardian", des, g_font, Black);
	name.SetPos(SCREEN_WIDTH - name.rect_.w - 20, 5);
	name.Render(des);

	SDL_SetRenderDrawColor(des, 0,0,0,255);
	SDL_Rect back_box = {SCREEN_WIDTH/2 + 14, name.rect_.y + name.rect_.h + 1, 616, 50};
	SDL_RenderFillRect(des, &back_box);

	SDL_SetRenderDrawColor(des, 255,255,255,255);
	int hlost = (20 - health)*600/20; //cout<<hlost;
	SDL_Rect mid_box = {back_box.x + 8 + hlost, back_box.y + 8, 600 - hlost, 34};
	SDL_RenderFillRect(des, &mid_box);

	SDL_SetRenderDrawColor(des, 255,0,0,255);

	SDL_Rect front_box = {back_box.x + 8 + hlost, back_box.y + 8, 600 - hlost, 34};
	SDL_RenderFillRect(des, &front_box);
}
void Boss1::Interaction(Player& player)
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

void Boss1::DoBoss(Map& map_data, Player& player, SDL_Renderer* des)
{
	y_val_ += BOSS_GRAV;
	if(y_val_ >= BOSS_CAP_SPEED) y_val_ = BOSS_CAP_SPEED;

	if(melee == 1) status_ = ATTACK1;
	if(health <= 0) status_ = DEATH;
	if(player.status_ == Player::DEATH) status_ = IDLE;
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
	else if(status_ == SPELL1)
	{
		if(global_search == 0)
		{
			int distance = (player.Box().x+player.Box().w/2) - (Box().x+Box().w/2);
			if(distance < 0) save_dir = LEFT;
			else save_dir = RIGHT;
			global_search = 1;
			can_spell = 1;
		}
	}
	else if(status_ == DEATH)
	{
		melee = 0;
		global_search = 0;
		rest_time = 1;
		can_shoot = 0;
		num_bullet = 3;
		active_punch = 0;
	}
	CheckColli(map_data);
	if(can_gensp && spell_wait)
	{
		can_gensp = 0;
		spell_wait--;
		Bullet blet;
		blet.LoadImg("map/Boss1/Boss-bullet2-0.png", des);
		blet.y_val_ = rnd(13,20);

			blet.dir = Bullet::BDOWN;
			blet.SetForBox(34,40,30,75);
			//SDL_Rect tBox = blet.Box(66, 69, 179, 65);
			//blet.SetPos(rect_.x, rect_.y + 50);
			blet.x_pos_ = player.rect_.x;
			blet.y_pos_ = -100;

		blet.is_move = 1;
		bullet_list.push_back(blet);
	}

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

void Boss1::SetMapXY(const int map_x, const int map_y)
{
	map_x_ = map_x; map_y_ = map_y;
	for(Bullet bullet: bullet_list)
	{
		bullet.SetMapXY(map_x, map_y);
	}
}
