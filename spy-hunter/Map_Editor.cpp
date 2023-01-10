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
	show_grid = true;

	clicked_button = false;
	clicked_button_id = 0;
	clicked_button_index = 0;

	board_shift_x = 200;
	board_shift_y = 5;
	tiles_container.x = board_shift_x;
	tiles_container.y = board_shift_y;
	tiles_container.w = 32 * 20;
	tiles_container.h = 32 * 15;
	selected_tile_id = 0;
	previos_selected_tile_button_index = 0;
	currently_open_map_index = -1;

	input_manager = Input_Manager::get_instance();
	asset_manager = Asset_Manager::get_instance();
	map_manager = Map_Manager::get_instance();

	fill_empty_map(tiles);
	search_for_files();
}

Map_Editor::~Map_Editor()
{
	input_manager->destroy_instance();
	asset_manager->destroy_instance();
	map_manager->destroy_instance();
}


//-------------------------------


void Map_Editor::run()
{
	buttons.add( { "New", {10, 10}, 100, 40, NEW } );
	buttons.add( { "Save", {10, 60}, 100, 40, SAVE} );
	buttons.add( { "Grid", {10, 110}, 100, 40, GRID} );

	for (int i = Map_Manager::tile_type::GRASS; i <= Map_Manager::tile_type::ROADSIDE_RIGHT_HALF; i++)
	{
		previos_selected_tile_button_index = buttons.add({ " ", {160.0f, 18.0f + i*41.0f}, 15, 15, SELECT + i });
	}

	buttons.element(previos_selected_tile_button_index).change_text("X");
	selected_tile_id = Map_Manager::tile_type::GRASS;

	//MAIN LOOP
	while(!quit)
	{
		if(e.type)


		while (SDL_PollEvent(&e) != 0)
		{
			if (e.window.event == SDL_WINDOWEVENT_MINIMIZED)
				while (SDL_WaitEvent(&e))
					if (e.window.event == SDL_WINDOWEVENT_RESTORED)
						break;

			if (e.type == SDL_QUIT)
				quit = true;
		}
			

		clicked_button = false;
		input_manager->update_mouse();

		for (int i = 0; i < buttons.size(); i++)
		{
			bool temp = buttons.element(i).update(input_manager);
			if (temp)
			{
				clicked_button_id = buttons.element(i).id;
				clicked_button_index = i;
				clicked_button = true;
			}
		}

		change_tile();
		handle_button_click();
		draw();
	}
}

void Map_Editor::draw()
{
	SDL_SetRenderTarget(Helper::renderer, NULL);
	SDL_SetRenderDrawColor(Helper::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Helper::renderer);

	//DRAW BUTTONS
	for (int i = 0; i < buttons.size(); i++)
		buttons.element(i).draw();


	//DRAW TILES TO SELECT
	for (int i = Map_Manager::tile_type::GRASS; i <= Map_Manager::tile_type::ROADSIDE_RIGHT_HALF; i++)
	{
		render_tile(i, 120, 10 + i * 42);
	}


	//DRAW TILES
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			render_tile(tiles[i][j], board_shift_x + j * 32, board_shift_y + i * 32);
		}
	}


	//DRAW GRID
	if (show_grid)
	{
		for (int i = 0; i <= 15; i++)
		{
			Helper::draw_line(board_shift_x, board_shift_y + i * 32, board_shift_x + 20 * 32, board_shift_y + i * 32);
		}

		for (int i = 0; i <= 20; i++)
		{
			Helper::draw_line(board_shift_x + i * 32, board_shift_y, board_shift_x + i * 32, board_shift_y + 15 * 32);
		}
	}

	SDL_RenderPresent(Helper::renderer);
}

void Map_Editor::handle_button_click()
{
	if (!clicked_button)
		return;

	if (clicked_button_id == NEW)
	{
		printf("Clicked new project button\n");

		Dynamic_String p = "./Assets/maps/map";
		FILE* file;
		file = fopen(p + files.size() + ".bin", "wb");
		fclose(file);
		files.add(p + files.size() + ".bin");
		add_file_button();
		fill_empty_map(tiles);
		currently_open_map_index = files.size() -1;
		save_map();
	}
	else if (clicked_button_id == SAVE)
	{
		printf("Clicked save project button for map: %s\n", files.element(currently_open_map_index));
		save_map();
	}
	else if (clicked_button_id == GRID)
	{
		printf("Changed grid visibility\n");
		show_grid = !show_grid;
	}
	else if (clicked_button_id >= LOAD && clicked_button_id < SELECT)
	{
		map_manager->load_map_from_file(files.element(clicked_button_id - LOAD), tiles);
		currently_open_map_index = clicked_button_id - LOAD;
		printf("Clicked load project button for file: %s\n", files.element(clicked_button_id - LOAD));
	}
	else if (clicked_button_id >= SELECT)
	{
		printf("Clicked select item button number: %d\n", clicked_button_id - SELECT);
		if (previos_selected_tile_button_index == clicked_button_id)
			return;

		buttons.element(previos_selected_tile_button_index).change_text(" ");
		buttons.element(clicked_button_index).change_text("X");
		selected_tile_id = clicked_button_id - SELECT;
		previos_selected_tile_button_index = clicked_button_index;
	}
}

void Map_Editor::search_for_files()
{
	FILE* file;
	int counter = 0;
	Dynamic_String path = "./Assets/maps/map";

	while (file = fopen(path + counter + ".bin", "r"))
	{
		files.add(path + counter + ".bin");
		printf("Found map file: %s \n", files.element(counter));
		add_file_button();
		counter++;
		fclose(file);
	}
}

void Map_Editor::change_tile()
{
	if (!input_manager->mouse_button_released())
		return;

	SDL_Rect m = input_manager->get_mouse_box();
	if (!SDL_HasIntersection(&m, &tiles_container))
		return;

	int tile_x_index = (m.x - board_shift_x) / 32;
	int tile_y_index = (m.y - board_shift_y) / 32;

	tiles[tile_y_index][tile_x_index] = selected_tile_id;
}

void Map_Editor::save_map()
{
	if (currently_open_map_index == -1)
		return;

	FILE* file;
	file = fopen(files.element(currently_open_map_index), "wb");
	Dynamic_Array<__int8> length(2);
	Dynamic_Array<__int8> distance(2);
	__int8 temp = 0;

	for (int i = 0; i < 15; i++)
	{
		check_row(i, length, distance);
		printf("Row number: %d, has %d roads\n", i, length.size());
		temp = length.size();
		fwrite(&temp, sizeof(__int8), 1, file);
		for (int i = 0; i < temp; i++)
		{
			fwrite(&distance.element(i), sizeof(__int8), 1, file);
			fwrite(&length.element(i), sizeof(__int8), 1, file);
		}
		length.clear();
		distance.clear();
	}


	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			fwrite(&tiles[i][j], sizeof(__int8), 1, file);
		}
	}

	fclose(file);

	FILE* dependencies = fopen("./Assets/maps/maps_dependencies.bin", "wb");
	FILE* map1, * map2;
	for (int i = 0; i < files.size(); i++)
	{
		map1 = fopen(files.element(i), "rb");
		for (int j = 0; j < files.size(); j++)
		{
			rewind(map1);
			map2 = fopen(files.element(j), "rb");

			if (check_compatibility_of_two_maps(map1, map2))
			{
				fwrite(&i, sizeof(__int8), 1, dependencies);
				fwrite(&j, sizeof(__int8), 1, dependencies);
				printf("Map: %s, is compatible with map: %s\n", files.element(i), files.element(j));
			}
			fclose(map2);
		}
		fclose(map1);
	}
	__int8 eof = -1;
	fwrite(&eof, sizeof(__int8), 1, dependencies);
	fclose(dependencies);
}

bool Map_Editor::check_compatibility_of_two_maps(FILE*& map1, FILE*& map2)
{
	__int8 map1_roads = 0;
	__int8 map2_roads = 0;

	for (int i = 0; i < 14; i++)
	{
		fread(&map2_roads, sizeof(__int8), 1, map2);
		for (int j = 0; j < map2_roads; j++)
		{
			fseek(map2, 2 * sizeof(__int8), SEEK_CUR);
		}
	}

	fread(&map1_roads, sizeof(__int8), 1, map1);
	fread(&map2_roads, sizeof(__int8), 1, map2);

	if (map1_roads != map2_roads)
		return false;


	__int8 map1_val;
	__int8 map2_val;
	bool flag = true;

	for (int i = 0; i < map1_roads*2; i++)
	{
		fread(&map1_val, sizeof(__int8), 1, map1);
		fread(&map2_val, sizeof(__int8), 1, map2);
		if (map1_val != map2_val)
		{
			flag = false;
			break;
		}
	}

	if (!flag)
		return false;

	return true;
}

void Map_Editor::check_row(int row, Dynamic_Array<__int8>& length, Dynamic_Array<__int8>& distance)
{
	int counter = 0;
	__int8 last_index = -1;
	int road_index_start = Map_Manager::tile_type::ROAD;
	int road_index_end = Map_Manager::tile_type::ROADSIDE_RIGHT_HALF;

	for (int i = 0; i < 20; i++)
	{
		//printf("%d", tiles[row][i]);
		if(tiles[row][i] >= road_index_start && tiles[row][i] <= road_index_end)
		{
			if (last_index >= road_index_start && last_index <= road_index_end)
			{
				counter++;
			}
			else
			{
				counter++;
				distance.add(i);
			}
		}
		else
		{
			if (last_index >= road_index_start && last_index <= road_index_end)
			{
				length.add(counter);
				counter = 0;
			}
		}
		last_index = tiles[row][i];
	}

	if (counter > 0)
	{
		length.add(counter);
	}

	//printf("Row number: %d, has %d roads, their data: \n", row, distance.size());
	//for (int i = 0; i < distance.size(); i++)
	//{
	//	printf("%d Distance: %d, length: %d\n", i, distance.element(i), length.element(i));
	//}
}

void Map_Editor::fill_empty_map(__int8 map[][20])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = Map_Manager::tile_type::GRASS;
		}
	}
}

void Map_Editor::add_file_button()
{
	int size = files.size() - 1;
	buttons.add({ Dynamic_String("map") + size, {10.0f, 220.0f + size * 30}, 100, 25, LOAD + size});
}

void Map_Editor::render_tile(int index, int x, int y)
{
	SDL_Rect clip;
	clip.x = index * 32;
	clip.y = 0;
	clip.w = 32;
	clip.h = 32;
	
	Helper::render_texture(asset_manager->tileset, x, y, &clip);
}