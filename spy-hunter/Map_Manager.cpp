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
	camera_move = 0;
	last_camera_y_pos = 0;
	map_count = -1;
	load_map_from_file("./Assets/maps/map0.bin", map_buffer);
	prepare_texture(current_map_texture);
	map_count = 0;
	load_map_from_file("./Assets/maps/map1.bin", map_buffer);
	prepare_texture(next_map_texture);
	map_count = 1;
	current_map_id = 0;
	next_map_id = 1;
	
}

Map_Manager::~Map_Manager()
{
	SDL_DestroyTexture(current_map_texture);
	SDL_DestroyTexture(next_map_texture);
}

//-------------------------------

void Map_Manager::update()
{
	if (Helper::camera_pos.y != last_camera_y_pos)
	{
		camera_move += Helper::camera_pos.y - last_camera_y_pos;
		last_camera_y_pos = Helper::camera_pos.y;

		if (camera_move <= -480.0)
		{
			camera_move += 480.0;
			change_next_map();
			map_count++;

			if(Helper::score_freeze_time <= 0)
				Helper::score += 100;
		}
	}
}

void Map_Manager::restart()
{
	camera_move = 0;
	last_camera_y_pos = 0;
	map_count = -1;
	load_map_from_file("./Assets/maps/map0.bin", map_buffer);
	prepare_texture(current_map_texture);
	map_count = 0;
	load_map_from_file("./Assets/maps/map1.bin", map_buffer);
	prepare_texture(next_map_texture);
	map_count = 1;
	current_map_id = 0;
	next_map_id = 1;
}

void Map_Manager::display_map()
{
	Helper::render_texture(next_map_texture, 0, -map_count*480-Helper::camera_pos.y, nullptr);
	Helper::render_texture(current_map_texture, 0, -(map_count-1)*480-Helper::camera_pos.y, nullptr);
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
	load_map_from_file(path + next_map_id + ".bin", map_buffer);
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
	current_map_id = next_map_id;
	next_map_id = rand() % compatible_maps.size();
}

void Map_Manager::load_map_from_file(const Dynamic_String& file_name, __int8 map[][20])
{
	FILE* file;
	file = fopen(file_name, "rb");

	if (file == NULL)
		return;

	__int8 number_of_roads = 0;
	__int8 distance_from_left_edge = 0;
	__int8 road_width = 0;
	
	
	for (int i = 0; i < 15; i++)
	{
		fread(&number_of_roads, sizeof(__int8), 1, file);
		for (int j = 0; j < number_of_roads; j++)
		{
			fread(&distance_from_left_edge, sizeof(__int8), 1, file);
			fread(&road_width, sizeof(__int8), 1, file);

			Object* left = new Object(Object::Object_Type::MAP_ELEMENT, { 0.0f, (i * 32.0f) - (map_count+1) * 480 }, 
				distance_from_left_edge * 32, 32, true, nullptr);

			Object::all_objects.add(left);
			if (j == number_of_roads - 1)
			{
				int temp = distance_from_left_edge + road_width;
				Object* right = new Object(Object::Object_Type::MAP_ELEMENT, {temp * 32.0f, (i * 32.0f) - (map_count + 1) * 480},
					(20-temp) * 32, 32, true, nullptr);

				Object::all_objects.add(right);
			}
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

void Map_Manager::get_safe_area_to_spawn(Dynamic_Array<int>& distance, Dynamic_Array<int>& width, Object* object)
{
	int current_row = -camera_move / 32;

	if (object != nullptr)
		current_row = (object->position.y - Helper::camera_pos.y) / 32;

	Dynamic_String path = "./Assets/maps/map";
	FILE* file = fopen(path + current_map_id + ".bin", "rb");

	__int8 number_of_roads = 0;
	__int8 distance_from_left_edge = 0;
	__int8 road_width = 0;

	for (int i = 0; i < current_row; i++)
	{
		fread(&number_of_roads, sizeof(__int8), 1, file);
		for (int j = 0; j < number_of_roads; j++)
		{
			fseek(file, 2, SEEK_CUR);
		}
	}

	fread(&number_of_roads, sizeof(__int8), 1, file);
	for (int i = 0; i < number_of_roads; i++)
	{
		fread(&distance_from_left_edge, sizeof(__int8), 1, file);
		fread(&road_width, sizeof(__int8), 1, file);
		distance.add(distance_from_left_edge);
		width.add(road_width);
	}

	fclose(file);
}