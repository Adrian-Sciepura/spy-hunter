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

	//player = new Object({ 100, 100 }, 60, 80, true, asset_manager->player_texture);
	player = new Player({ 100, 100 }, 60, 80, true, 20, asset_manager->player_texture);
	//static_cast<Entity*>(player)->is_moving = true;
	//static_cast<Entity*>(player)->speed = 40;
	//player->speed = 50;
	//entities.add({ asset_manager->player_texture, {100, 500}, 80 });
	//entities.add({ asset_manager->tree_texture, {300, 80}, 0 });
	//entities.add({ asset_manager->tree_texture, {230, 180}, 0 });
	//entities.add({ asset_manager->tree_texture, {300, 280}, 0 });

	camera_manager->set_target(player);
}

Game_Manager::~Game_Manager()
{
	input_manager->destroy_instance();
	time_manager->destroy_instance();
	camera_manager->destroy_instance();
	asset_manager->destroy_instance();
	map_manager->destroy_instance();
	delete player;
}

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
		player->update();
		//entities.element(0).update_movement();
		camera_manager->update();
		draw();
	}
}

void Game_Manager::draw()
{
	SDL_SetRenderDrawColor(Helper::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Helper::renderer);
	map_manager->get_next_map();

	//for (int i = 0; i < entities.size(); i++)
	//{
	//	entities.element(i).draw(camera_manager->get_camera_pos());
	//}
	player->draw(camera_manager->get_camera_pos());
	SDL_RenderPresent(Helper::renderer);
}

void Game_Manager::update_entities()
{

}