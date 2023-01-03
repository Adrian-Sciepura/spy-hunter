#include "Time_Manager.h"

Time_Manager* Time_Manager::instance = nullptr;

Time_Manager* Time_Manager::get_instance()
{
	if (instance == nullptr)
		instance = new Time_Manager();
	return instance;
}

void Time_Manager::destroy_instance()
{
	if (instance == nullptr)
		return;
	delete instance;
	instance = nullptr;
}

Time_Manager::Time_Manager()
{
	delta = 0.0f;
	last_update = 0;
	elapsed_ticks = 0;
}

void Time_Manager::update()
{
	elapsed_ticks = SDL_GetTicks() - last_update;
	delta = elapsed_ticks * 0.001f;
	last_update = SDL_GetTicks();
}

float Time_Manager::get_delta()
{
	return this->delta;
}