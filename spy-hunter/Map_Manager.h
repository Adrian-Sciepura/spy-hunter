#define _CRT_SECURE_NO_WARNINGS
#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Helper.h"
#include "Dynamic_String.h"
#include "Asset_Manager.h"
#include <cstdio>
#include <time.h>

class Map_Manager
{
private:
	static Map_Manager* instance;

	SDL_Texture* current_map_texture;
	SDL_Texture* next_map_texture;
	__int8 map_buffer[15][20];
	int current_map_id;
	int row_in_next_map;
	int camera_move;

	Map_Manager();
	~Map_Manager();

public:
	int last_camera_y_pos;
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

	void update(int camera_y_pos);
	void display_map();
	void render_tile(int index, int x, int y);
	void prepare_texture(SDL_Texture*& texture);
	void change_next_map();
	void get_next_map();

	void load_map_from_file(const Dynamic_String& file_name, __int8 map[][20]);
};

#endif