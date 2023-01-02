#ifndef ENTITY_H
#define ENTITY_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Vector2.h"
#include "Helper.h"

class Entity
{
public:

	Vector2 position;
	SDL_Texture* texture;

	Entity(SDL_Texture* texture);

	void draw();
};

#endif

