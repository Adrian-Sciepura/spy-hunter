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

	realized_points = SDL_CreateRGBSurface(0, 190, 25, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	Uint32 color = SDL_MapRGB(realized_points->format, 150, 149, 153);
	SDL_FillRect(realized_points, NULL, color);
	Helper::render_text(asset_manager->font, realized_points, "a b c d e f h i j k l", false);

	header = SDL_CreateRGBSurface(0, Helper::SCREEN_WIDTH, 30, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_FillRect(header, NULL, 0);
	
	quit = false;
	pause = false;
	minimized_window = false;

	player = new Player({ 300, 300 }, 32, 53, true, 220, asset_manager->player_texture);
	Object::all_objects.add(player);

	camera_manager->set_target(player);
}

Game_Manager::~Game_Manager()
{
	input_manager->destroy_instance();
	time_manager->destroy_instance();
	camera_manager->destroy_instance();
	asset_manager->destroy_instance();
	map_manager->destroy_instance();

	SDL_FreeSurface(realized_points);
	SDL_FreeSurface(header);
	
	for (int i = 0; i < Object::all_objects.size(); i++)
	{
		delete Object::all_objects.element(i);
	}
	Object::all_objects.clear();
}


//---------------------------------

void Game_Manager::run()
{
	while (!quit)
	{
		early_update();
		update();
		late_update();
	}
}

void Game_Manager::early_update()
{
	//EVENT HANDLER
	while (SDL_PollEvent(&e))
	{
		if (e.window.event == SDL_WINDOWEVENT_MINIMIZED)
		{
			minimized_window = true;
			pause = true;
		}

		if (e.window.event == SDL_WINDOWEVENT_RESTORED)
		{
			minimized_window = false;
			pause = false;
		}

		if (e.type == SDL_QUIT)
			quit = true;
	}

	if (input_manager->key_released(SDL_SCANCODE_P))
	{
		pause = !pause;
		time_manager->pause();
	}
	else if (input_manager->key_pressed(SDL_SCANCODE_N) || player->lives_left < 0)
	{
		time_manager->restart();
		Helper::score = 0;
		Helper::infinite_life_timer = 30.0;
		Helper::score_freeze_time = 0;
		Helper::camera_pos = { 0,0 };

		for (int i = 0; i < Object::all_objects.size(); i++)
		{
			delete Object::all_objects.element(i);
		}

		Object::all_objects.clear();

		player = new Player({ 300, 300 }, 32, 53, true, 220, asset_manager->player_texture);
		Object::all_objects.add(player);

		map_manager->restart();
		camera_manager->set_target(player);
	}
	else if (input_manager->key_released(SDL_SCANCODE_ESCAPE))
	{
		quit = true;
	}

	//UPDATE TIME
	time_manager->update();

	//UPDATE HEADER
	SDL_FillRect(header, NULL, 0);
	Helper::render_text(asset_manager->font, header, header_text, true);

	//FRAME LIMITER
	if (Helper::FRAME_DELAY > time_manager->get_delta())
	{
		SDL_Delay((Helper::FRAME_DELAY - time_manager->get_delta()) * 1000);
	}

	if (!pause)
	{
		if (Helper::infinite_life_timer > 0)
		{
			Helper::infinite_life_timer -= time_manager->delta;
			sprintf(header_text, "TIME: %.1lf s  %02d  SCORE: %08d", time_manager->get_elapsed_time(), (int)Helper::infinite_life_timer, Helper::score);
		}
		else
		{
			sprintf(header_text, "TIME: %.1lf s  %d\003  SCORE: %08d", time_manager->get_elapsed_time(), player->lives_left, Helper::score);
		}
	}

}

void Game_Manager::update()
{
	//GAME UPDATE
	if (pause)
		return;

	if (Helper::score_freeze_time > 0)
		Helper::score_freeze_time -= time_manager->delta;

	for (int i = 0; i < Object::all_objects.size(); i++)
	{
		Object::all_objects.element(i)->update();
	}

	camera_manager->update();
	map_manager->update();
	
	Object::cleanup();
	spawn_cars();
}

void Game_Manager::late_update()
{
	input_manager->update_keyboard();

	if (!minimized_window)
		draw();
}

void Game_Manager::draw()
{
	SDL_SetRenderTarget(Helper::renderer, NULL);
	SDL_SetRenderDrawColor(Helper::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Helper::renderer);
	
	//DRAW MAP
	map_manager->display_map();
	
	//DRAW OBJECTS
	for (int i = 0; i < Object::all_objects.size(); i++)
	{
		Object::all_objects.element(i)->draw();
	}

	Helper::render_surface(realized_points, Helper::SCREEN_WIDTH - 190, Helper::SCREEN_HEIGHT - 25);
	Helper::render_surface(header, 0, 0);
	SDL_RenderPresent(Helper::renderer);
}

void Game_Manager::spawn_cars()
{
	if (AI_Vehicle::number_of_objects > 0 || player->total_distance < 800)
		return;

	srand(time(NULL));
	Dynamic_Array<int> distance;
	Dynamic_Array<int> width;
	map_manager->get_safe_area_to_spawn(distance, width);
	
	int num_of_road_tiles = 0;
	for (int i = 0; i < width.size(); i++)
		num_of_road_tiles += (width.element(i)-2);

	int how_many_to_create = rand() % 3 + 1;
	int tiles_per_car = num_of_road_tiles / how_many_to_create;

	for (int i = 0; i < how_many_to_create; i++)
	{
		int tile_x = rand() % tiles_per_car + i * tiles_per_car + 1;
		int which_road = 0;
		int temp = 0;
		while (true)
		{
			temp += (width.element(which_road) - 2);
			if (temp < tile_x)
				which_road++;
			else
				break;
		}

		int pos_x = (distance.element(which_road) + tile_x) * 32;
		int type = rand() % 3;
		if(type == 0)
		{
			Neutral* neutral_car = new Neutral({ (float)pos_x, Helper::camera_pos.y + 500 }, player->speed + (rand() % 12 + 5));
			Object::all_objects.add(neutral_car);
		}
		else
		{
			Enemy* enemy_car = new Enemy({ (float)pos_x, Helper::camera_pos.y + 500 }, player->speed + (rand() % 12 + 5));
			Object::all_objects.add(enemy_car);
		}
		
	}
}