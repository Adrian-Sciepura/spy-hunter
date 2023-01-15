#ifndef ENTITY_H
#define ENTITY_H

#include "Object.h"
#include "Time_Manager.h"

class Entity: public Object
{
public:
	float total_distance;
	float speed;
	float max_speed;
	float angle;
	bool is_moving;

	float knockback;
	float knockback_angle;
	

	Entity(Object_Type type, const Vector2& position, int width, int height, bool is_solid, float max_speed, SDL_Texture* texture);
	Entity(const Entity& entity);
	
	virtual void update_movement();
	virtual void update() override;
	virtual void die();
};

#endif