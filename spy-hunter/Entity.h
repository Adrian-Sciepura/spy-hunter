#ifndef ENTITY_H
#define ENTITY_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Vector2.h"
#include "Helper.h"
#include "Box_Collider.h"

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

	Entity(SDL_Texture* texture, const Vector2& position);
	void draw();
	void update_collisions();

};

#endif

