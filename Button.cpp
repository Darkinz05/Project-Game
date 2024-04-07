#include "Button.h"

Button::Button()
{
	is_hovered = 0;
	press = 0;
	advance = 0;
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
		cout<<event.motion.x<<" "<<event.motion.y<<"\n";
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
	if(is_hovered == 0)
	{
		BaseObject::LoadTTF(text, des, font, button_out);
	}
	else
	{
		BaseObject::LoadTTF(text, des, font, button_in);
	}

	BaseObject::Render(des);
}
