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

void Button::Show(SDL_Renderer* des)
{
	if(press) BaseObject::LoadImg("menu/Button_down.png",des);
	else BaseObject::LoadImg("menu/Button_up.png", des);
	BaseObject::SetRect(0,0);
	BaseObject::Render(des);
}
