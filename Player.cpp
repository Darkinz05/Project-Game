#include "CommonFunc.h"
#include "Player.h"

Player::Player()
{
	frame_cur_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	input_type_.jump_ = 0;
	map_x_ = 0;
	map_y_ = 0;

}

Player::~Player()
{

}

bool Player::LoadImg(string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if(ret == true)
	{
		width_frame_ = rect_.w/8;
		height_frame_ = rect_.h;
	}
	//cout<<ret<<" ";
	return ret;
}

void Player::SetClip()
{
	if(width_frame_ > 0 && height_frame_ > 0)
	{
		for(int i=0; i<8; i++)
		{
			clip[i].x = i*width_frame_;
			clip[i].y = 0;
			clip[i].w = width_frame_;
			clip[i].h = height_frame_;
		}
	}
	width_frame_ = TILE_SIZE-1;
	height_frame_ = TILE_SIZE-1;
}

void Player::Show(SDL_Renderer* des)
{
	if(status_ == WALK_LEFT)
	{
		LoadImg("Character/knight_left.png", des);
	}
	else
	{
		LoadImg("Character/knight_right.png", des);
	}

	if(input_type_.left_ == 1 || input_type_.right_ ==1)
	{
		frame_cur_++;//move
	}
	else frame_cur_ = 0;//idle
	if(frame_cur_ == 8*4) frame_cur_ = 0;

	rect_.x = x_pos_ - map_x_;
	//cout<<x_pos_<<" "<<map_x_<<"\n";
	rect_.y = y_pos_ - map_y_;

	width_frame_ = TILE_SIZE-1;
	height_frame_ = TILE_SIZE-1;
	SDL_Rect* current_clip = &clip[frame_cur_/4];// * = &//cout<<width_frame_<<" "<<height_frame_<<"\n";

	SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};// tao tu hu khong -> ko dung pointer
	//cout<<rect_.x<<" "<<rect_.y<<" "<<width_frame_<<" "<<height_frame_<<" "<<frame_cur_<<"\n";

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void Player::HandleInputAction(SDL_Event e)
{
	if(e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			break;
		case SDLK_LEFT:
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			break;
		case SDLK_UP:
			input_type_.jump_ = 1;
			break;
		default:
			break;
		}

	}
	else if(e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
			input_type_.right_ = 0;
			break;
		case SDLK_LEFT:
			input_type_.left_ = 0;
			break;
		default:
			break;
		}
	}

}

void Player::DoPlayer(Map& map_data)
{

	x_val_ = 0;
	y_val_ += GRAV;

	if(y_val_ >= CAP_SPEED)
	{
		y_val_ = CAP_SPEED;
	}

	if(input_type_.left_ == 1)
	{
		x_val_ -= PLAYER_SPEED;
	}
	else if(input_type_.right_ == 1)
	{
		x_val_ += PLAYER_SPEED;
	}

	if(input_type_.jump_ == 1)
	{
		if(on_ground_ == 1)
		{
			y_val_ = -PLAYER_JUMP_SPEED;
		}
		on_ground_ = 0;
		input_type_.jump_ = 0;
	}
	CheckColli(map_data);
	CenterEntityOnMap(map_data);
}

void Player::CheckColli(Map& map_data)
{
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;
	//cout<<x_val_<<" "<<y_val_<<"\n";
	//Check horizontal: x
	int height_min = height_frame_<TILE_SIZE ? height_frame_:TILE_SIZE;

	x1 = (x_pos_+x_val_) / TILE_SIZE;// o nao cua map //trai
	x2 = (x_pos_+x_val_+width_frame_-1) / TILE_SIZE; //phai cuar nhan vat

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_+height_min-1) / TILE_SIZE;

	if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
	{
		if(x_val_ > 0) //moving to right
		{
			if(map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
			{
				x_pos_ = x2*TILE_SIZE - width_frame_ ;
				x_val_ = 0;
			}
		}
		else if(x_val_ < 0)
		{
			if(map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0)
			{
				x_pos_ = (x1+1)*TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	//check vertical
	int width_min_ = width_frame_<TILE_SIZE ? width_frame_:TILE_SIZE;

	x1 = (x_pos_) / TILE_SIZE;// o nao cua map //trai
	x2 = (x_pos_+width_min_-1) / TILE_SIZE; //phai cuar nhan vat

	y1 = (y_pos_+y_val_) / TILE_SIZE;
	y2 = (y_pos_+y_val_+height_frame_-1) / TILE_SIZE;

	if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
	{
		if(y_val_ > 0)
		{
			if(map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0)
			{

				y_pos_ = y2*TILE_SIZE - height_frame_;

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
			if(map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
			{
				y_pos_ = (y1+1)*TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;
	//cout<<x_pos_<<" "<<y_pos_<<"\n";

	if(x_pos_ < 0) x_pos_ = 0;
	else if(x_pos_ + width_frame_ > map_data.max_x_)
	{
		//cout<<1;
		x_pos_ = map_data.max_x_ - width_frame_ - 1;// max x la diem pixel cuoi cuar map
	}

	//cout<<x_pos_<<" "<<y_pos_<<"\n";
	//cout<<on_ground_<<" ";
}

void Player::CenterEntityOnMap(Map& map_data)// set start_x_y// camera
{
	map_data.start_x_ = x_pos_ + width_frame_/2 - (SCREEN_WIDTH/2) + 50;// return to cemter
	if(map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ + height_frame_/2 - (SCREEN_HEIGHT/2);
	if(map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
	//cout<<1<<"\n";
}
