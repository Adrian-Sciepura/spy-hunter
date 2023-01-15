#include "Entity.h"

Entity::Entity(Object_Type type, const Vector2& position, int width, int height, bool is_solid, float max_speed, SDL_Texture* texture) :
	Object(type, position, width, height, is_solid, texture)
{
	this->total_distance = 0;
	this->max_speed = max_speed;
	this->speed = 0;
	this->is_moving = false;
	this->angle = 90.0f;
	this->knockback = 0;
	this->knockback_angle = 90.0f;
}

Entity::Entity(const Entity& entity) :
	Entity(entity.type, entity.position, entity.width, entity.height, entity.is_solid, entity.max_speed, entity.texture)
{
	
}

void Entity::update_movement()
{
	if (speed > 0)
	{
		is_moving = true;
		float move_dist = speed * Time_Manager::get_instance()->get_delta() * 4.0;
		float move_x = move_dist * cos(angle * Helper::PI / 180.0);
		float move_y = move_dist * -sin(angle * Helper::PI / 180.0);
		total_distance += abs(move_y);
		position += {move_x, move_y};
	}
	else
	{
		is_moving = false;
	}

	if (knockback > 0)
	{
		float move_knock = knockback * Time_Manager::get_instance()->get_delta() * 4.0;
		float knock_x = move_knock * cos((knockback_angle) * Helper::PI / 180.0);
		float knock_y = move_knock * -sin(knockback_angle * Helper::PI / 180.0);
		position += {knock_x, knock_y};
		knockback -= move_knock;
	}
}

void Entity::update()
{
	update_movement();
	Object::update();
}

void Entity::die()
{
	health = 0;
}