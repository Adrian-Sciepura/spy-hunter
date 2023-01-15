#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <crtdbg.h>

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"

#include "Helper.h"
#include "Game_Manager.h"
#include "Map_Editor.h"

void init(SDL_Window*& window, int screen_width, int screen_height, float screen_scale)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init error");
		exit(1);
	}
	
	window = SDL_CreateWindow("Adrian Sciepura 193350", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screen_width * screen_scale, screen_height * screen_scale, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		SDL_Quit();
		printf("SDL_Window error"); 
		exit(1);
	}

	Helper::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Helper::renderer == nullptr)
	{
		SDL_Quit();
		printf("SDL_Renderer error"); 
		exit(1);
	}

	SDL_RenderSetLogicalSize(Helper::renderer, screen_width, screen_height);
}

int main(int argc, char** argv) 
{
	SDL_Window *window;

	if (argc > 1)
	{
		if (strcmp(argv[1], "-map_editor") == 0)
		{
			init(Helper::window, 850, 500, Helper::SCREEN_SCALE);
			printf("MAP EDITOR \n");
			Map_Editor* map_editor = Map_Editor::get_instance();
			map_editor->run();
			map_editor->destroy_instance();
		}
	}
	else
	{
		init(Helper::window, Helper::SCREEN_WIDTH, Helper::SCREEN_HEIGHT, Helper::SCREEN_SCALE);
		SDL_ShowCursor(SDL_DISABLE);
		Game_Manager* game = Game_Manager::get_instance();
		game->run();
		game->destroy_instance();
	}

	SDL_DestroyRenderer(Helper::renderer);
	SDL_DestroyWindow(Helper::window);
	SDL_Quit();
	_CrtDumpMemoryLeaks();
	return 0;
};
