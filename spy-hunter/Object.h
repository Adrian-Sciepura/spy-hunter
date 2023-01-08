#ifndef OBJECT_H
#define OBJECT_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Box_Collider.h"
#include "Helper.h"
#include <cstdio>

class Object
{
public:
	Vector2 position;
	SDL_Texture* texture;
	Box_Collider collider;
	bool is_solid;
	int width;
	int height;

	Object(const Vector2& position, int width, int height, bool is_solid, SDL_Texture* texture = nullptr);
	Object(const Object& object);

	virtual void update();
	//void update_collisions();
	void draw(const Vector2& camera_pos);
};

#endif