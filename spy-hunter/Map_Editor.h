#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <malloc.h>
#include <cstdio>
#include <cstdlib>

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"

#include "Helper.h"
//#include "Dynamic_Array.h"
#include "Input_Manager.h"
#include "Asset_Manager.h"
#include "Map_Manager.h"
#include "UI_Button.h"


class Map_Editor
{
private:

	enum Button_ID
	{
		NEW,
		SAVE,
		GRID,
		LOAD,
		SELECT = 100,
	};

	static Map_Editor* instance;

	bool quit;
	bool clicked_button;
	bool show_grid;
	int clicked_button_id;
	int clicked_button_index;
	int board_shift_x, board_shift_y;
	int selected_tile_id;
	int previos_selected_tile_button_index;
	int currently_open_map_index;
	__int8 tiles[15][20];

	SDL_Event e;
	SDL_Rect tiles_container;

	Input_Manager* input_manager;
	Asset_Manager* asset_manager;
	Map_Manager* map_manager;

	Dynamic_Array<UI_Button> buttons;
	Dynamic_Array<Dynamic_String> files;

	Map_Editor();
	~Map_Editor();

public:
	static Map_Editor* get_instance();
	static void destroy_instance();

	void run();
	void draw();

	void handle_button_click();
	void change_tile();
	void search_for_files();
	void save_map();
	void fill_empty_map(__int8 map[][20]);
	void add_file_button();
	void render_tile(int index, int x, int y);
};

#endif