#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"

#include <cstdio>

class Time_Manager
{
private:
	static Time_Manager* instance;
	
	int last_update;
	int elapsed_ticks;
	int start_ticks;
	bool stop;

	Time_Manager();
	~Time_Manager();

public:
	static Time_Manager* get_instance();
	static void destroy_instance();

	float delta;

	void update();
	void pause();
	void restart();

	float get_elapsed_time();
	float get_delta();
};

#endif