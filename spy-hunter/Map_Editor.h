#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <malloc.h>
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Dynamic_Array.h"
#include "Input_Manager.h"
#include "Helper.h"
#include "UI_Button.h"
#include <cstdio>

class Map_Editor
{
private:
	static Map_Editor* instance;

	bool quit;
	int clicked_button_id;
	SDL_Event e;
	Input_Manager* input_manager;
	Dynamic_Array<UI_Button> buttons;

	Map_Editor();
	~Map_Editor();

public:
	static Map_Editor* get_instance();
	static void destroy_instance();

	void run();
	void draw();

	void handle_button_click(int id);
};

#endif