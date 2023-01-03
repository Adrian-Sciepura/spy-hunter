#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"

class Time_Manager
{
private:
	static Time_Manager* instance;

	float delta;
	int last_update;
	int elapsed_ticks;

	Time_Manager();

public:
	static Time_Manager* get_instance();
	static void destroy_instance();

	void update();
	float get_delta();
};

#endif

