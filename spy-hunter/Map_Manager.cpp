#include "Map_Manager.h"

Map_Manager* Map_Manager::instance = nullptr;

Map_Manager* Map_Manager::get_instance()
{
	if (instance == nullptr)
		instance = new Map_Manager();
	return instance;
}

void Map_Manager::destroy_instance()
{
	if (instance == nullptr)
		return;
	delete instance;
	instance = nullptr;
}

Map_Manager::Map_Manager()
{
	srand(time(NULL));
	row_in_next_map = 0;
	camera_move = 0;
	last_camera_y_pos = 0;
	load_map_from_file("./Assets/maps/map0.bin", map_buffer);
	prepare_texture(current_map_texture);
	load_map_from_file("./Assets/maps/map1.bin", map_buffer);
	prepare_texture(next_map_texture);
	current_map_id = 1;
	
}

Map_Manager::~Map_Manager()
{
	SDL_DestroyTexture(current_map_texture);
	SDL_DestroyTexture(next_map_texture);
}

//-------------------------------

void Map_Manager::update(int camera_y_pos)
{
	if (camera_y_pos != last_camera_y_pos)
	{
		camera_move += camera_y_pos - last_camera_y_pos;
		last_camera_y_pos = camera_y_pos;
		if (camera_move <= -32)
		{
			camera_move = 0;
			row_in_next_map += 1;
		}
		//printf("Camera y move: %d\n", camera_move);
	}
}


void Map_Manager::display_map()
{
	if (row_in_next_map >= 15)
	{
		change_next_map();
		row_in_next_map = 0;
	}
		

	////int row = 0;
	////for (int i = 0; i < 20; i++)
	////{
	////	render_tile(next_map[14 - row_in_next_map][i], i * 32, abs(camera_move)-32);
	////}

	//for (int i = 15 - row_in_next_map-1; i < 15; i++)
	//{
	//	for (int j = 0; j < 20; j++)
	//	{
	//		render_tile(next_map[i][j], j * 32, row * 32 - camera_move-32);
	//	}
	//	row++;
	//}

	//for (int i = 0; i < 15 - row_in_next_map; i++)
	//{
	//	for (int j = 0; j < 20; j++)
	//	{
	//		render_tile(current_map[i][j], j * 32, row * 32 - camera_move-32);
	//	}
	//	row++;
	//}

	//SDL_Rect n_map;
	//SDL_Rect c_map;
	//n_map.x = 0;
	//n_map.y = (15 - row_in_next_map)*32;
	//n_map.w = 640;
	//n_map.h = row_in_next_map * 32;

	//c_map.x = 0;
	//c_map.y = row_in_next_map * 32;;
	//c_map.w = 640;
	//c_map.h = (15 - row_in_next_map) * 32;
	
	
	//Helper::render_texture(next_map_texture, 0, -camera_move, &n_map);
	//Helper::render_texture(current_map_texture, 0, row_in_next_map * 32 - camera_move, &c_map);

	Helper::render_texture(next_map_texture, 0, (row_in_next_map - 15) * 32 - camera_move, nullptr);
	Helper::render_texture(current_map_texture, 0, row_in_next_map * 32 - camera_move, nullptr);
}

void Map_Manager::render_tile(int index, int x, int y)
{
	SDL_Rect clip;
	clip.x = index * 32;
	clip.y = 0;
	clip.w = 32;
	clip.h = 32;

	Helper::render_texture(Asset_Manager::get_instance()->tileset, x, y, &clip);
}

void Map_Manager::prepare_texture(SDL_Texture*& texture)
{
	texture = SDL_CreateTexture(Helper::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Helper::SCREEN_WIDTH, Helper::SCREEN_HEIGHT);
	SDL_SetRenderTarget(Helper::renderer, texture);


	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			render_tile(map_buffer[i][j], j * 32, i * 32);
		}
	}
	SDL_SetRenderTarget(Helper::renderer, NULL);
}


void Map_Manager::change_next_map()
{
	get_next_map();
	Dynamic_String path = "./Assets/maps/map";
	load_map_from_file(path + current_map_id + ".bin", map_buffer);
	SDL_DestroyTexture(current_map_texture);
	current_map_texture = next_map_texture;
	next_map_texture = nullptr;
	prepare_texture(next_map_texture);
}

void Map_Manager::get_next_map()
{
	FILE* dependencies = fopen("./Assets/maps/maps_dependencies.bin", "rb");
	Dynamic_Array<__int8> compatible_maps(2);
	__int8 id = 0;
	__int8 value = 0;

	while (true)
	{
		fread(&id, sizeof(__int8), 1, dependencies);
		if (id == -1)
			break;

		if (id != current_map_id)
		{
			fseek(dependencies, 1, SEEK_CUR);
			continue;
		}

		fread(&value, sizeof(__int8), 1, dependencies);
		compatible_maps.add(value);
	}
	fclose(dependencies);

	current_map_id = rand() % compatible_maps.size();
}


void Map_Manager::load_map_from_file(const Dynamic_String& file_name, __int8 map[][20])
{
	FILE* file;
	file = fopen(file_name, "rb");

	if (file == NULL)
		return;

	__int8 temp = 0;
	__int8 temp2 = 0;
	
	
	for (int i = 0; i < 15; i++)
	{
		fread(&temp, sizeof(__int8), 1, file);
		for (int j = 0; j < temp; j++)
		{
			fread(&temp2, sizeof(__int8), 1, file);
			fread(&temp2, sizeof(__int8), 1, file);
		}
	}


	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			__int8 temp;
			fread(&temp, sizeof(__int8), 1, file);
			map[i][j] = temp;
		}
	}
	fclose(file);
}

