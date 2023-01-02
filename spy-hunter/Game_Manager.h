#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Input_Manager.h"
#include "Time_Manager.h"
#include "Entity.h"
#include "Helper.h"

class Game_Manager
{
private:
	static Game_Manager* instance;
	Input_Manager* input_manager;
	Time_Manager* time_manager;
	
	SDL_Event e;
	Entity* player;
	bool quit;

	Game_Manager();
	~Game_Manager();

public:
	static Game_Manager* get_instance();
	static void destroy_instance();
	void run();
	void draw();
};

#endif

