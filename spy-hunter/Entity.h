#ifndef ENTITY_H
#define ENTITY_H

#include "Object.h"
#include "Time_Manager.h"

class Entity: public Object
{
public:
	float speed;
	float max_speed;
	float angle;
	bool is_moving;

	Entity(const Vector2& position, int width, int height, bool is_solid, float max_speed, SDL_Texture* texture);
	Entity(const Entity& entity);
	
	virtual void update_movement();
	virtual void update() override;
};

#endif