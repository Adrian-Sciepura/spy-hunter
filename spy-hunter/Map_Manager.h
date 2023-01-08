#define _CRT_SECURE_NO_WARNINGS
#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Helper.h"
#include "Dynamic_String.h"
#include <cstdio>
#include "Asset_Manager.h"

class Map_Manager
{
private:
	static Map_Manager* instance;

	__int8 current_map[15][20];
	__int8 next_map[15][20];

	Map_Manager();
	~Map_Manager();

public:
	enum tile_type
	{
		GRASS,
		GRASS_FLOWERS_YELLOW,
		GRASS_FLOWERS_RED,
		ROAD,
		ROADSIDE_LEFT,
		ROADSIDE_LEFT_CORNER,
		ROADSIDE_LEFT_HALF,
		ROADSIDE_RIGHT,
		ROADSIDE_RIGHT_CORNER,
		ROADSIDE_RIGHT_HALF
	};

	static Map_Manager* get_instance();
	static void destroy_instance();

	void get_next_map();
	void remove_previous_map();

	void generate_next_row();
	void remove_last_row();

	void load_map_from_file(const Dynamic_String& file_name, __int8 map[][20]);
};

#endif