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
#include "AI_Vehicle.h"
#include "Enemy.h"
#include "Neutral.h"
#include "Helper.h"

#include <cstdio>
#include <cstring>

class Game_Manager
{
private:
	static Game_Manager* instance;

	Input_Manager* input_manager;
	Time_Manager* time_manager;
	Camera_Manager* camera_manager;
	Asset_Manager* asset_manager;
	Map_Manager* map_manager;

	SDL_Surface* realized_points;
	SDL_Surface* header;
	char header_text[100];

	Player* player;
	SDL_Event e;

	bool pause;
	bool minimized_window;
	bool quit;
	
	Game_Manager();
	~Game_Manager();

public:
	static Game_Manager* get_instance();
	static void destroy_instance();


	void run();
	void early_update();
	void update();
	void late_update();
	void draw();

	void spawn_cars();
};

#endif