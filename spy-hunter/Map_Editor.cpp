#include "Map_Editor.h"

Map_Editor* Map_Editor::instance = nullptr;

Map_Editor* Map_Editor::get_instance()
{
	if (instance == nullptr)
		instance = new Map_Editor();
	return instance;
}

void Map_Editor::destroy_instance()
{
	if (instance == nullptr)
		return;
	delete instance;
	instance = nullptr;
}

Map_Editor::Map_Editor()
{
	quit = false;
	clicked_button_id = 0;
	input_manager = Input_Manager::get_instance();
}

Map_Editor::~Map_Editor()
{
	input_manager->destroy_instance();
	input_manager = nullptr;
}

void Map_Editor::run()
{
	buttons.add( { {10, 10}, 100, 40, 0 } );

	while(!quit)
	{
		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
				quit = true;

		input_manager->update_mouse();
		for (int i = 0; i < buttons.size(); i++)
			buttons.element(i).update();


		draw();
	}
}

void Map_Editor::draw()
{
	SDL_SetRenderDrawColor(Helper::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Helper::renderer);

	for (int i = 0; i < buttons.size(); i++)
		buttons.element(i).draw();

	SDL_RenderPresent(Helper::renderer);
}

void handle_button_click(int id)
{

}

