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
	
	quit = false;
	SDL_Texture* player_texture = Helper::load_texture("./Assets/car.bmp");
	player = new Entity(player_texture);
	player->position = { 100, 100 };
}

Game_Manager::~Game_Manager()
{
	Input_Manager::destroy_instance();
	Time_Manager::destroy_instance();

	input_manager = nullptr;
	time_manager = nullptr;
}

void Game_Manager::run()
{
	

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
				quit = true;

		time_manager->update();
		input_manager->update();
		

		if (input_manager->key_pressed(SDL_SCANCODE_UP))
		{

		}

		if (input_manager->key_pressed(SDL_SCANCODE_DOWN))
		{

		}

		if (input_manager->key_pressed(SDL_SCANCODE_LEFT))
		{

		}

		if (input_manager->key_pressed(SDL_SCANCODE_RIGHT))
		{

		}


		draw();
	}
}

void Game_Manager::draw()
{
	SDL_SetRenderDrawColor(Helper::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Helper::renderer);

	player->draw();

	SDL_RenderPresent(Helper::renderer);
}