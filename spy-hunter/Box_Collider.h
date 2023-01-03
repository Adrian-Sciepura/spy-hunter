#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Vector2.h"
#include "Helper.h"

class Box_Collider
{
private:
	void draw();

public:
	static bool show;

	SDL_Rect* box;
	Vector2 offset;
	bool is_colliding;

	Box_Collider(const Vector2& size, const Vector2& offset);
	~Box_Collider();
	void update(const Vector2& object_pos);
	bool check_collision(const Box_Collider& collider);
};

#endif