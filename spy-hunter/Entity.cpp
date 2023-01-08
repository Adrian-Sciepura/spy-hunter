#include "Entity.h"

Entity::Entity(const Vector2& position, int width, int height, bool is_solid, float max_speed, SDL_Texture* texture) :
	Object(position, width, height, is_solid, texture)
{
	this->max_speed = max_speed;
	this->speed = 0;
	this->is_moving = false;
	this->angle = 90.0f;
}

Entity::Entity(const Entity& entity) :
	Entity(entity.position, entity.width, entity.height, entity.is_solid, entity.max_speed, entity.texture)
{
	
}

void Entity::update_movement()
{
	if (is_moving)
	{
		float move_dist = speed * Time_Manager::get_instance()->get_delta() * 4.0;
		float move_x = move_dist * cos(angle * Helper::PI / 180.0);
		float move_y = move_dist * -sin(angle * Helper::PI / 180.0);

		position += {move_x, move_y};
	}
}

void Entity::update()
{
	Object::update();
	update_movement();
}