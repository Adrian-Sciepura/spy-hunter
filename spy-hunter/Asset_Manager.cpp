#include "Asset_Manager.h"

Asset_Manager* Asset_Manager::instance = nullptr;

Asset_Manager* Asset_Manager::get_instance()
{
	if (instance == nullptr)
		instance = new Asset_Manager();
	return instance;
}

void Asset_Manager::destroy_instance()
{
	if (instance == nullptr)
		return;
	delete instance;
	instance = nullptr;
}

Asset_Manager::Asset_Manager()
{
	player_texture = Helper::load_texture("./Assets/car.bmp");
	enemy_texture = Helper::load_texture("./Assets/enemy.bmp");
	neutral_texture = Helper::load_texture("./Assets/neutral.bmp");
	bullet_texture = Helper::load_texture("./Assets/bullet.bmp");
	tileset = Helper::load_texture("./Assets/tileset.bmp");
	font = SDL_LoadBMP("./Assets/font.bmp");
	SDL_SetColorKey(font, true, 0x000000);
}

Asset_Manager::~Asset_Manager()
{	
	SDL_DestroyTexture(player_texture);
	SDL_DestroyTexture(enemy_texture);
	SDL_DestroyTexture(neutral_texture);
	SDL_DestroyTexture(bullet_texture);
	SDL_DestroyTexture(tileset);
	SDL_FreeSurface(font);
}