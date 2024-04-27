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
pair<float, float> calculateDir(float fromX, float fromY, float toX, float toY)
{
    float dx = toX - fromX;
    float dy = toY - fromY;
    float length = sqrt(dx * dx + dy * dy);
    pair<float, float> direction;
    direction.first = (dx / length);
    direction.second = (dy / length);
    return direction;
}
Boss2::Boss2()
{
	frame_cur_ = 0;
	frame_eff_ = 0;
	x_pos_ = 700;
	y_pos_ = 112;
	x_val_ = 0;
	y_val_ = 0;
	reached = 0;
	hades = 0;
	num_out = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = 0;
	pre_status_ = -2;
	save_dir = LEFT;
	til_next = 0;
	melee = 0;
	global_search = 0;
	rest_time = 2;
	can_shoot = 1;
	num_bullet = 3;
	active_punch = 0;
	health = 30;
	invincible = 0;
	over = 0;
	spell_time = 0;
	spell_wait = 0;
	can_gensp = 1;
	can_spell = 1;
	st_eff = 0;
	phase = 1;
	trans = 0;
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
	status_ = rnd(1,3);
	if(status_ == 3)
	{
		int x= rnd(0,5);
		if(x==0) status_ = rnd(1,2);

	}
	hades = 0;
	can_shoot = 1;
	spell_time = 0;
	global_search = 0;
}

void Boss2::Show(SDL_Renderer* des)
{

	if(pre_status_ != status_)
	{
		hades = 0;
		can_shoot = 1;
		can_spell = 1;
		global_search = 0;
		frame_cur_ = 0;
	}
	else if(paused == 0 )frame_cur_++;
	pre_status_ = status_;
	if(status_ == SLAM || status_ == SHOOT1)
	{
		if(frame_cur_ == 0) Mix_PlayChannel(-1, boss1_attack, 0);
	}
	if(status_ == IDLE)
	{
		hades = 0;
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
	else if(status_ == MOVE1 )
	{
		if(frame_cur_ == 4*num_sprite2[status_])
		{
			frame_cur_ = 0;
		}
		string path = "map/Boss2/Boss-idle-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
	}
	else if(status_ == SHOOT1)
	{
		if(frame_cur_ == 3*num_sprite2[status_])
		{
			frame_cur_ = 3*num_sprite2[status_]-1;
			if(can_shoot == 1)
			{
				Bullet blet;
				blet.name = "map/Boss2/bullet.png";
				blet.LoadImg("map/Boss2/bullet.png", des);
				blet.x_val_ = rnd(25, 33);
				if(phase == 2) blet.x_val_ = rnd(40,50);
				if(save_dir == LEFT)
				{
					blet.dir = Bullet::BLEFT;
					blet.SetForBox(0,0,blet.rect_.w,blet.rect_.h);
					blet.x_pos_ = rect_.x - blet.Box().w - 30;
					blet.y_pos_ = rect_.y + 160;
				}
				else if(save_dir == RIGHT)
				{
					blet.dir = Bullet::BRIGHT;
					blet.SetForBox(0,0,blet.rect_.w,blet.rect_.h);
					blet.x_pos_ = rect_.x + rect_.w - 100;
					blet.y_pos_ = rect_.y + 160;
				}
				blet.is_move = 1;
				bullet_list.push_back(blet);
				can_shoot = 0;
			}
		}
		for(int i=(int)bullet_list.size()-1; i>=0; --i)
		{
			Bullet *x = &bullet_list[i];
			if(x->change && x->dir == Bullet::BLEFT && x->x_pos_ <= x_pos_ + rect_.w - 100)
			{
				x->is_move = 0;
				status_ = MOVE2;
				x_des_ = 700;
				y_des_ = 112;
				vec = calculateDir(rect_.x, rect_.y, x_des_, y_des_);
				reached = 0;
				//cout<<2222;
			}
			else if(x->change && x->dir == Bullet::BRIGHT && x->x_pos_ >= x_pos_)
			{
				x->is_move = 0;
				status_ = MOVE2;
				x_des_ = 700;
				y_des_ = 112;
				vec = calculateDir(rect_.x, rect_.y, x_des_, y_des_);
				reached = 0;
			}
		}

		string path = "map/Boss2/Boss-shoot1-" + to_string(frame_cur_/3) + ".png";
		LoadImg(path, des);

//		if(bullet_list.size() == 0)
//		{
//			status_ = MOVE2;
//		}
	}
	else if(status_ == MOVE2)
	{
		if(frame_cur_ == 4*num_sprite2[status_])
		{
			frame_cur_ = 0;
		}
		string path = "map/Boss2/Boss-idle-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
	}
	else if(status_ == SLEEP)
	{
		if(frame_cur_ == 4*num_sprite2[status_])
		{
			frame_cur_ = 4*num_sprite2[status_]-1;

		}
		string path = "map/Boss2/Boss-sleep-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);

		if(spell_time == 4)
		{
			spell_time = 0;
			rest_time = rnd(2,3);
			status_ = IDLE;
		}
	}
	else if(status_ == TRANS)
	{
		if(frame_cur_ == 4*num_sprite2[status_])
		{
			frame_cur_ = 0;
			trans++;
		}
		string path = "map/Boss2/Boss-trans-" + to_string(frame_cur_/4) + ".png";
		LoadImg(path, des);
		if(trans == 2)
		{
			rest_time = rnd(2,3);
			status_ = IDLE;
		}
	}
	ShowEffect(des);
	int tmp = 0;

	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RendererFlip flip_type = SDL_FLIP_NONE;
	if(save_dir == RIGHT) flip_type = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(des, p_object_, NULL, &renderQuad, 0, NULL, flip_type);

	ShowBullet(des);
}
void Boss2::ShowBullet(SDL_Renderer* des)
{
	for(int i=(int)bullet_list.size()-1; i>=0; --i)
	{
		Bullet *x = &bullet_list[i];

		if(x->is_move)
		{
			int type = 0;
			if(x->dir == Bullet::BLEFT || x->dir == Bullet::BRIGHT) type = 0;
			else type = 2;
			type = 3;
			if(paused == 0) x->Move();
			x->Show(des, type);

		}
		else
		{
			if(x->dir == Bullet::BLEFT && x->change == 0)
			{
				Bullet blet;
				blet.name = "map/Boss2/bullet.png";
				blet.LoadImg("map/Boss2/bullet.png", des);
				blet.x_val_ = x->x_val_;
				blet.dir = Bullet::BRIGHT;
				blet.SetForBox(0,0,blet.rect_.w,blet.rect_.h);
				blet.x_pos_ = -50;
				blet.y_pos_ = x->y_pos_;
				blet.change = 1;
				blet.is_move = 1;
				bullet_list.push_back(blet);

			}
			else if(x->dir == Bullet::BRIGHT && x->change == 0)
			{
				Bullet blet;
				blet.name = "map/Boss2/bullet.png";
				blet.LoadImg("map/Boss2/bullet.png", des);
				blet.x_val_ = x->x_val_;
				blet.dir = Bullet::BLEFT;
				blet.SetForBox(0,0,blet.rect_.w,blet.rect_.h);
				blet.x_pos_ = SCREEN_WIDTH + 50;
				blet.y_pos_ = x->y_pos_;
				blet.change = 1;
				blet.is_move = 1;
				bullet_list.push_back(blet);
			}

			if(x->dir == Bullet::BDOWN)
			{
				num_out++;
				num_out%= ((phase == 1) ? 4:6);
				if(num_out == 0) can_spell = 1;
			}
			bullet_list.erase(bullet_list.begin() + i);
		}
	}
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
		aura.LoadImg(path, des);
		//cout<<frame_eff_/2<<" ";
		if(phase == 1)
		{
			SDL_Rect renderQuad = {rect_.x + 60, rect_.y + 60, aura.rect_.w, aura.rect_.h};
			SDL_RendererFlip flip_type = SDL_FLIP_NONE;
			SDL_RenderCopyEx(des, aura.p_object_, NULL, &renderQuad, 0, NULL, flip_type);
		}
		else
		{
			SDL_Rect renderQuad = {rect_.x + 10, rect_.y + 60, aura.rect_.w, aura.rect_.h};
			SDL_RendererFlip flip_type = SDL_FLIP_NONE;
			SDL_RenderCopyEx(des, aura.p_object_, NULL, &renderQuad, 0, NULL, flip_type);

			renderQuad = {rect_.x + 110, rect_.y + 60, aura.rect_.w, aura.rect_.h};

			SDL_RenderCopyEx(des, aura.p_object_, NULL, &renderQuad, 0, NULL, flip_type);
		}

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

		if(status_ == SLEEP && get_hit)
		{
			health = min(30, health+1);
			invincible = 20;
		}
		if(status_ == SLEEP) get_hit = 0;
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
	else if(status_ == IDLE && health <= 15 && phase == 1)
	{
		phase = 2;
		status_ = TRANS;
	}

	if(player.status_ == Player::DEATH) status_ = IDLE;

	if(status_ == MOVE1 && hades == 0)
	{
		x_des_ = rnd(0,1) ? 900 : 0;
		y_des_ = rnd(0,3);
		if(y_des_ <= 1)
		{
			y_des_ = rnd(150, 170);
		}
		else y_des_ = rnd(250, 280);
		vec = calculateDir(rect_.x, rect_.y, x_des_, y_des_);
		hades = 1;
	}
	x_val_ = 0;
	y_val_ = 0;

	if(status_ == IDLE)
	{
		hades = 0;
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
		hades = 0;
		if(save_dir == LEFT) x_val_ = -BOSS_SPEED;
		else x_val_ = BOSS_SPEED;
	}
	else if(status_ == MOVE1)
	{
		//cout<<"x22 "<<vec.first<<" "<<vec.second<<"\n";
		x_val_ += vec.first*20;//speed
		y_val_ += vec.second*20;

		//cout<<x_val_<<" "<<y_val_<<"\n";
		if(x_val_ < 0) save_dir = LEFT;
		else save_dir = RIGHT;
		//cout<<x_des_<<" "<<y_des_<<"\n";
	}
	else if(status_ == MOVE2)
	{
		if(reached == 0)
		{
			float dx = x_des_ - rect_.x;
            float dy = y_des_ - rect_.y;
            float length = std::sqrt(dx * dx + dy * dy);
            //cout<<x_des_<<" "<<rect_.x<<"   "<<dx<<" "<<dy<<" "<<length<<"\n";
            if(length <= 20)
			{
				reached = 1;
				x_val_ = 0;
				y_val_ = 0;
				x_pos_ = x_des_;
				y_pos_ = y_des_;
			}
			else
			{
				float directionX = dx / length;
                float directionY = dy / length;
                x_val_ += directionX*20;
                y_val_ += directionY*20;
			}
		}
		else
		{
			hades = 0;
			status_ = IDLE;
			rest_time = rnd(2,3);
			melee = 0;
		}
		if(x_val_ < 0) save_dir = LEFT;
		else save_dir = RIGHT;
		//cout<<x_val_<<" "<<y_val_<<"\n";
	}
	else if(status_ == SLEEP)
	{
		if(frame_cur_ == 4*num_sprite2[status_] - 1 && can_spell)
		{
			spell_time++;
			Mix_PlayChannel(-1, boss1_attack, 0);
			for(int i=1; i<= ((phase == 1) ? 4:6); ++i)
			{
				Bullet blet;
				blet.name = "map/Boss2/bullet-fall.png";
				blet.LoadImg("map/Boss2/bullet-fall.png", des);
				blet.y_val_ = rnd(15,15);

				blet.dir = Bullet::BDOWN;
				blet.SetForBox(0,0,blet.rect_.w,blet.rect_.h);
				//SDL_Rect tBox = blet.Box(66, 69, 179, 65);
				//blet.SetPos(rect_.x, rect_.y + 50);
				if(i == 1) blet.x_pos_ = player.x_pos_ + 10;
				else blet.x_pos_ = rnd(0, 1000);
				blet.y_pos_ = -100;

				blet.is_move = 1;
				bullet_list.push_back(blet);
				can_spell = 0;
			}
		}
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
		if(status_ == MOVE1) status_ = SHOOT1;
	}
	else if(x_pos_ + rect_.w - 100 > map_data.max_x_)
	{
		if(status_ == MOVE1) status_ = SHOOT1;
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
