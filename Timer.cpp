#include "Timer.h"
#include "CommonFunc.h"
Timer::Timer()
{
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = 0;
	is_started_ = 0;
}

Timer::~Timer()
{

}

void Timer::start()
{
	is_started_ = 1;
	is_paused_ = 0;
	start_tick_ = SDL_GetTicks();
}
void Timer::stop()
{
	is_paused_ = 0;
	is_started_ = 0;
}

void Timer::paused()
{
	if(is_started_ == true && is_paused_ == false)
	{
		is_paused_ = 1;
		paused_tick_	= SDL_GetTicks() - start_tick_;
	}
}

void Timer::unpaused()
{
	if(is_paused_ == true)
	{
		is_paused_ = 0;
		start_tick_ = SDL_GetTicks()-paused_tick_;
		paused_tick_ = 0;
	}
}

int Timer::getTicks()
{
	if(is_started_ == 1)
	{
		if(is_paused_ == 1)
		{
			return paused_tick_;
		}
		else return SDL_GetTicks() - start_tick_;
	}

	return 0;
}

