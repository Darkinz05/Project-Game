
#include "BaseObject.h"

BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	Free();

	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if(load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, keyR, keyG, keyB));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if(new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}

	p_object_ = new_texture;

	return p_object_ != NULL;
}

void BaseObject::Show(SDL_Renderer* des)
{
	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};// tao tu hu khong -> ko dung pointer
	//cout<<renderQuad.x<<" "<<renderQuad.y<<" "<<renderQuad.w<<" "<<renderQuad.h<<"\n";
	//cout<<x_pos_<<" "<<map_x_<<"    "<<y_pos_<< " "<<map_y_<<"\n";
	SDL_RendererFlip flip_type = SDL_FLIP_NONE;

	SDL_RenderCopyEx(des, p_object_, NULL, &renderQuad, 0, NULL, flip_type);
}

bool BaseObject::LoadTTF(std::string text, SDL_Renderer* screen, TTF_Font* font, SDL_Color text_color)
{
	Free();
	SDL_Surface* load_surface = TTF_RenderText_Blended(font, text.c_str(),text_color);
	p_object_ = SDL_CreateTextureFromSurface(screen, load_surface);
	if(p_object_ != NULL)
	{
		rect_.w = load_surface->w;
		rect_.h = load_surface->h;
	}
	SDL_FreeSurface(load_surface);
	return p_object_ != NULL;
}
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
	if(p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}
