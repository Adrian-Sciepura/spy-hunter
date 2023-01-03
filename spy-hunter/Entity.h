#ifndef ENTITY_H
#define ENTITY_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Vector2.h"
#include "Helper.h"
#include "Box_Collider.h"
#include "Input_Manager.h"
#include "Time_Manager.h"

class Entity
{
private:
	static Entity** entities;

public:
	static int number_of_entities;
	static Entity** get_all_entities();
	static int get_number_of_entities();
	static void remove_all_entities();

	Vector2 position;
	SDL_Texture* texture;
	Box_Collider* collider;
	float speed;
	float max_speed;
	float angle;
	bool is_moving;

	Entity(SDL_Texture* texture, const Vector2& position, float max_speed);
	void draw(const Vector2& camera_pos);
	void update_collisions();
	//void change_angle();
	void update_movement();

};

#endif

