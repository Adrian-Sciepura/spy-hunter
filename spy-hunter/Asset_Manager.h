#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Helper.h"
#include "Dynamic_Array.h"
#include <cstdio>

class Asset_Manager
{
private:
	static Asset_Manager* instance;
	Asset_Manager();
	~Asset_Manager();

	void load_tileset();
public:
	static Asset_Manager* get_instance();
	static void destroy_instance();

	SDL_Texture* player_texture;
	SDL_Texture* tree_texture;
	SDL_Texture* tileset;
	Dynamic_Array<SDL_Rect> tileset_info;
	SDL_Surface* font;
};

#endif