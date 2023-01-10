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
	quit = false;

	Player* player = new Player({ 100, 300 }, 60, 80, true, 300, asset_manager->player_texture);
	Object* tree = new Object({ 300.0, 80.0 }, 30, 60, true, asset_manager->tree_texture);
	objects.add(tree);
	objects.add(player);

	camera_manager->set_target(player);
}

Game_Manager::~Game_Manager()
{
	input_manager->destroy_instance();
	time_manager->destroy_instance();
	camera_manager->destroy_instance();
	asset_manager->destroy_instance();
	map_manager->destroy_instance();
	
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects.element(i);
	}
}


//---------------------------------


void Game_Manager::run()
{	

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.window.event == SDL_WINDOWEVENT_MINIMIZED)
				while (SDL_WaitEvent(&e))
					if (e.window.event == SDL_WINDOWEVENT_RESTORED)
						break;

			if (e.type == SDL_QUIT)
				quit = true;
		}

		time_manager->update();
		input_manager->update_keyboard();

		for (int i = 0; i < objects.size(); i++)
		{
			objects.element(i)->update();
		}

		map_manager->update(camera_manager->get_camera_pos().y);
		camera_manager->update();
		draw();
	}
}

void Game_Manager::draw()
{
	SDL_SetRenderTarget(Helper::renderer, NULL);
	SDL_SetRenderDrawColor(Helper::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Helper::renderer);
	map_manager->display_map();

	for (int i = 0; i < objects.size(); i++)
	{
		objects.element(i)->draw(camera_manager->get_camera_pos());
	}

	SDL_RenderPresent(Helper::renderer);
}