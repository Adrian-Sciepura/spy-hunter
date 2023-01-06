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
	asset_manager = Asset_Manager::get_instance();
	
	tiles_x = 20;
	tiles_y = 15;

	current_map = new __int8*[tiles_y];
	next_map = new __int8*[tiles_y];

	for (int i = 0; i < tiles_y; i++)
	{
		current_map[i] = new __int8[tiles_x];
		next_map[i] = new __int8[tiles_x];
	}
	load_map_from_file("./Assets/maps/map1.bin", current_map);
}

Map_Manager::~Map_Manager()
{
	for (int i = 0; i < tiles_y; i++)
	{
		delete[] current_map[i];
		delete[] next_map[i];
		//printf("destroyed: %d \n", i);
	}
	delete[] current_map;
	delete[] next_map;
}

//------------------------------

void Map_Manager::get_next_map()
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 20; j++)
			if (current_map[i][j] == GRASS)
				Helper::render_texture(asset_manager->grass_tile, Helper::renderer, j*32, i*32, nullptr);
}

void Map_Manager::remove_previous_map()
{

}

void Map_Manager::generate_next_row()
{

}

void Map_Manager::remove_last_row()
{

}

void Map_Manager::load_map_from_file(const Dynamic_String& file_name, __int8**& map)
{
	FILE* file;
	file = fopen("./Assets/map1.bin", "rb");

	if (file == NULL)
		return;

	//__int8 how_many_grass_areas_exist;
	//fread(&how_many_grass_areas_exist, sizeof(__int8), 1, file);

	//for (int i = 0; i < how_many_grass_areas_exist; i++)
	//{
	//	//TODO
	//}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			__int8 temp;
			fread(&temp, sizeof(__int8), 1, file);
			current_map[i][j] = temp;
			printf("Wartosc dla x = %d    y = %d   wynosi %d \n", j, i, current_map[i][j]);
		}
	}

	fclose(file);
}