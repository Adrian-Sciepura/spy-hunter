#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#define _CRT_SECURE_NO_WARNINGS

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"

#include "Input_Manager.h"
#include "Time_Manager.h"
#include "Camera_Manager.h"
#include "Asset_Manager.h"
#include "Map_Manager.h"

#include "Object.h"
#include "Entity.h"
#include "Player.h"
#include "Helper.h"
#include <cstdio>



class Game_Manager
{
private:
	static Game_Manager* instance;

	Input_Manager* input_manager;
	Time_Manager* time_manager;
	Camera_Manager* camera_manager;
	Asset_Manager* asset_manager;
	Map_Manager* map_manager;
	
	SDL_Event e;
	Object* player;
	//Entity** entities;
	//Dynamic_Array<Entity> entities;
	bool quit;

	Game_Manager();
	~Game_Manager();

public:
	static Game_Manager* get_instance();
	static void destroy_instance();
	void run();
	void draw();
	void update_entities();
};

#endif

