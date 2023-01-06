#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Helper.h"
#include "Game_Manager.h"
#include "Map_Editor.h"


int main(int argc, char** argv) {
	bool quit = false;
	SDL_Event event;
	SDL_Window *window;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init error");
		return 1;
	}
                              
	window = SDL_CreateWindow("Spy Hunter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		Helper::SCREEN_WIDTH * Helper::SCREEN_SCALE, Helper::SCREEN_HEIGHT * Helper::SCREEN_SCALE, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		SDL_Quit();
		printf("SDL_Window error");
		return 1;
	}

	Helper::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Helper::renderer == nullptr)
	{
		SDL_Quit();
		printf("SDL_Renderer error");
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(Helper::renderer, Helper::SCREEN_WIDTH, Helper::SCREEN_HEIGHT);


	if (argc > 1)
	{
		if (strcmp(argv[1], "-map_editor") == 0)
		{
			printf("MAP EDITOR \n");
			Map_Editor* map_editor = Map_Editor::get_instance();
			map_editor->run();
			map_editor->destroy_instance();
			map_editor = nullptr;
		}
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
		Game_Manager* game = Game_Manager::get_instance();
		game->run();
		game->destroy_instance();
		game = nullptr;
	}

	SDL_DestroyRenderer(Helper::renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
};
