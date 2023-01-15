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
	enum Object_Type
	{
		MAP_ELEMENT,
		BULLET,
		PLAYER,
		ENEMY,
		NEUTRAL
	};

	static Dynamic_Array<Object*> all_objects;
	static constexpr int delete_range = Helper::SCREEN_HEIGHT + 100;
	static void cleanup();

	Object_Type type;
	Vector2 position;
	SDL_Texture* texture;
	Dynamic_Array<Box_Collider*> colliders;
	Dynamic_Array<Object*> collisions;
	bool is_solid;
	int width;
	int height;
	int all_collisions;
	int health;

	Object(Object_Type type, const Vector2& position, int width, int height, bool is_solid, SDL_Texture* texture = nullptr);
	Object(const Object& object);
	virtual ~Object();

	virtual void update();
	virtual void update_collisions(int collider_index);
	void draw();
};

#endif