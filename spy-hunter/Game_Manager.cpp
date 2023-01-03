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
	entities = Entity::get_all_entities();

	quit = false;
	SDL_Texture* player_texture = Helper::load_texture("./Assets/car.bmp");
	SDL_Texture* tree_texture = Helper::load_texture("./Assets/tree.bmp");

	Entity* player = new Entity(player_texture, { 100, 100 });
	Entity* tree = new Entity(tree_texture, {300, 80});
	Entity* tree2 = new Entity(tree_texture, {230, 180});
	Entity* tree3 = new Entity(tree_texture, {300, 280});
}

Game_Manager::~Game_Manager()
{
	Input_Manager::destroy_instance();
	Time_Manager::destroy_instance();

	input_manager = nullptr;
	time_manager = nullptr;

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
		input_manager->update();
		
		float speed = 80.0 * 4.0 * time_manager->get_delta();

		if (input_manager->key_pressed(SDL_SCANCODE_UP))
		{
			player->position -= {0, speed};
		}

		if (input_manager->key_pressed(SDL_SCANCODE_DOWN))
		{
			player->position += {0, speed};
		}

		if (input_manager->key_pressed(SDL_SCANCODE_LEFT))
		{
			player->position -= {speed, 0};
		}

		if (input_manager->key_pressed(SDL_SCANCODE_RIGHT))
		{
			player->position += {speed, 0};
		}

		for (int i = 0; i < Entity::number_of_entities; i++)
		{
			entities[i]->update_collisions();
		}

		draw();
	}
}

void Game_Manager::draw()
{
	SDL_SetRenderDrawColor(Helper::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Helper::renderer);

	int temp = Entity::number_of_entities;
	for (int i = 0; i < temp; i++)
	{
		entities[i]->draw();
	}

	SDL_RenderPresent(Helper::renderer);
}