#include "Game_Manager.h"

Game_Manager* Game_Manager::instance = nullptr;

Game_Manager* Game_Manager::get_instance()
{
	if (instance == nullptr)
		instance = new Game_Manager();
	return instance;
}

void Game_Manager::destroy_instance()
{
	if (instance == nullptr)
		return;
	delete instance;
	instance = nullptr;
}

Game_Manager::Game_Manager()
{
	input_manager = Input_Manager::get_instance();
	time_manager = Time_Manager::get_instance();
	camera_manager = Camera_Manager::get_instance();
	asset_manager = Asset_Manager::get_instance();
	map_manager = Map_Manager::get_instance();

	entities = Entity::get_all_entities();
	quit = false;

	Entity* player = new Entity(asset_manager->player_texture, { 100, 500 }, 80);
	Entity* tree = new Entity(asset_manager->tree_texture, {300, 80}, 0);
	Entity* tree2 = new Entity(asset_manager->tree_texture, {230, 180}, 0);
	Entity* tree3 = new Entity(asset_manager->tree_texture, {300, 280}, 0);

	camera_manager->set_target(player);
}

Game_Manager::~Game_Manager()
{
	input_manager->destroy_instance();
	time_manager->destroy_instance();
	camera_manager->destroy_instance();
	asset_manager->destroy_instance();
	map_manager->destroy_instance();

	input_manager = nullptr;
	time_manager = nullptr;
	camera_manager = nullptr;
	asset_manager = nullptr;
	map_manager = nullptr;

	Entity::remove_all_entities();
	entities = nullptr;
}

void Game_Manager::run()
{
	Entity* player = entities[0];
	

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
				quit = true;

		time_manager->update();
		input_manager->update_keyboard();

		player->update_movement();
		

		for (int i = 0; i < Entity::number_of_entities; i++)
		{
			entities[i]->update_collisions();
		}

		camera_manager->update();
		draw();
	}
}

void Game_Manager::draw()
{
	SDL_SetRenderDrawColor(Helper::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Helper::renderer);
	map_manager->get_next_map();
	int temp = Entity::number_of_entities;
	for (int i = 0; i < temp; i++)
	{
		entities[i]->draw(camera_manager->get_camera_pos());
	}

	SDL_RenderPresent(Helper::renderer);
}