#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Vector2.h"
#include "Helper.h"
#include <cstdio>

class Box_Collider
{
public:
	static bool show;

	SDL_Rect box;
	Vector2 offset;
	bool is_colliding;
	bool is_trigger;

	Box_Collider();
	Box_Collider(int width, int height, bool is_trigger, const Vector2& offset);
	Box_Collider(const Box_Collider& collider);

	void update(const Vector2& object_pos);
	bool check_collision(const Box_Collider& collider);
	void draw(const Vector2& pos);
};

#endif