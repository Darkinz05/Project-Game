#include "Button.h"

Button::Button()
{
	is_hovered = 0;
	press = 0;
	advance = 0;
	lock = 0;
}

Button::~Button()
{

}

void Button::HandleInput(SDL_Event event)
{
	if(event.type == SDL_MOUSEMOTION)
	{
		if(is_hovered!=isInBound(event.motion.x, event.motion.y))
		{
			is_hovered = !is_hovered;
		}
		//cout<<event.motion.x<<" "<<event.motion.y<<"\n";
	}
	if(press == 1 && event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && is_hovered)
	{
		advance = 1;
	}
	if(event.type == SDL_MOUSEBUTTONUP) press = 0;
	if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && is_hovered)
	{
		press = 1;
	}

}

void Button::Show(SDL_Renderer* des, TTF_Font* font, int type, string text)
{
//	if(press) BaseObject::LoadImg("menu/Button_down.png",des);
//	else BaseObject::LoadImg("menu/Button_up.png", des);
	if(type == 1) // xu li text
	{
		if(is_hovered == 0)
		{
			BaseObject::LoadTTF(text, des, font, button_out);
		}
		else
		{
			BaseObject::LoadTTF(text, des, font, button_in);
		}
	}
	else if(type == 2)
	{
		if(lock) text = text + "-lock.png";
		else if(is_hovered == 0)
		{
			text = text + ".png";
		}
		else
		{
			text = text + "-hv.png";
		}

		//cout<<text<<"\n";
		BaseObject::LoadImg(text, des);
	}
	else if(type == 3)
	{
		text = text + ".png";
		BaseObject::LoadImg(text, des);
	}

	BaseObject::Render(des);
}
