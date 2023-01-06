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
	Asset_Manager* asset_manager;

	enum tile_type
	{
		ROAD,
		ROAD_SIDE_LEFT,
		ROAD_SIDE_RIGHT,
		GRASS,
		WATER
	};

	unsigned __int8 tiles_x;
	unsigned __int8 tiles_y;

	__int8** current_map;
	__int8** next_map;


	Map_Manager();
	~Map_Manager();

public:
	static Map_Manager* get_instance();
	static void destroy_instance();

	void get_next_map();
	void remove_previous_map();

	void generate_next_row();
	void remove_last_row();

	void load_map_from_file(const Dynamic_String& file_name, __int8**& map);
};

#endif