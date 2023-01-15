#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Helper.h"
#include <cstdio>

class Asset_Manager
{
private:
	static Asset_Manager* instance;
	Asset_Manager();
	~Asset_Manager();

public:
	static Asset_Manager* get_instance();
	static void destroy_instance();

	SDL_Texture* player_texture;
	SDL_Texture* enemy_texture;
	SDL_Texture* neutral_texture;
	SDL_Texture* bullet_texture;
	SDL_Texture* tileset;
	SDL_Surface* font;
};

#endif