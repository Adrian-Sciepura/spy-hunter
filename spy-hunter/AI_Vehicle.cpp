#include "AI_Vehicle.h"

const int AI_Vehicle::check_range = 40;
int AI_Vehicle::number_of_objects = 0;

AI_Vehicle::AI_Vehicle(Object_Type type, const Vector2& position, float speed, SDL_Texture* texture) :
	Entity(Object_Type::ENEMY, position, 32, 53, true, 220, texture)
{
	this->last_collision = Object_Type::MAP_ELEMENT;
	this->is_moving = true;
	this->speed = speed;
	this->left_check = new Box_Collider{ check_range, 1, false, { -check_range, 26.5f} };
	this->right_check = new Box_Collider{ check_range, 1, false, { float(width), 26.5f} };
	this->colliders.add(left_check);
	this->colliders.add(right_check);
	number_of_objects++;
}

AI_Vehicle::~AI_Vehicle()
{
	number_of_objects--;
}

void AI_Vehicle::update_collisions(int collider_index)
{
	if (collider_index == 2 && all_collisions == 0)
	{
		angle = 90;
		return;
	}

	switch (collider_index)
	{
		case 0:	//MAIN COLLIDER 
		{
			for (int i = 0; i < collisions.size(); i++)
			{
				main_collider_collision(collisions.element(i));
			}
			break;
		}
		case 1:	//LEFT CHECK
		{
			for (int i = 0; i < collisions.size(); i++)
			{
				left_check_collision(collisions.element(i));
			}
			break;
		}
		case 2:	//RIGHT CHECK
		{
			for (int i = 0; i < collisions.size(); i++)
			{
				right_check_collision(collisions.element(i));
			}
			break;
		}
	}
}

void AI_Vehicle::main_collider_collision(Object* collision)
{
	if (collision->type == Object_Type::PLAYER || 
		collision->type == Object_Type::ENEMY ||
		collision->type == Object_Type::NEUTRAL)
	{
		Entity* entity = static_cast<Entity*>(collision);
		float dx = position.x - entity->position.x;
		float dy = position.y - entity->position.y;
		float angle_between = atan2(dx, dy) * 180 / Helper::PI + 90;

		knockback_angle = 180 + angle_between;
		knockback = 0.5 * entity->speed;

		if (angle == 90)
		{
			knockback = 1.5 * entity->speed;
		}
	}
	else if (collision->type == Object_Type::MAP_ELEMENT)
	{
		if(health > 0)
			die();
	}
	else if (collision->type == Object_Type::BULLET)
	{
		if (health > 0)
			die();
	}

	if (collision->type != MAP_ELEMENT)
		last_collision = collision->type;
}

void AI_Vehicle::left_check_collision(Object* collision)
{

}

void AI_Vehicle::right_check_collision(Object* collision)
{

}