#include "Player.h"

Player::Player(const Vector2& position, int width, int height, bool is_solid, float max_speed, SDL_Texture* texture) :
	Entity(Object_Type::PLAYER, position, width, height, is_solid, max_speed, texture)
{
	this->lives_left = 0;
}

void Player::update_movement()
{
	Input_Manager* input = Input_Manager::get_instance();

	if (!input->key_pressed(SDL_SCANCODE_UP) && speed == 0)
		is_moving = false;

	if (input->key_pressed(SDL_SCANCODE_UP))
	{
		is_moving = true;
		if(speed + 0.5 <= max_speed)
			speed += 0.5;

		if (input->key_pressed(SDL_SCANCODE_LEFT))
			angle = 110;
		else if (input->key_pressed(SDL_SCANCODE_RIGHT))
			angle = 70;
		else
			angle = 90;
	}
	else if (input->key_pressed(SDL_SCANCODE_DOWN))
	{
		if(speed - 0.5 >= 0)
			speed -= 0.5;

		if (input->key_pressed(SDL_SCANCODE_LEFT))
			angle = 110;
		else if (input->key_pressed(SDL_SCANCODE_RIGHT))
			angle = 70;
		else
			angle = 90;
	}
	else if (is_moving)
	{
		if (input->key_pressed(SDL_SCANCODE_LEFT))
			angle = 110;
		else if (input->key_pressed(SDL_SCANCODE_RIGHT))
			angle = 70;
		else
			angle = 90;
	}

	Entity::update_movement();
	//printf("Object row: %f\n", (this->position.y - Helper::camera_pos.y) / 32);
	if (input->key_released(SDL_SCANCODE_SPACE))
	{
		Bullet* bullet = new Bullet({ this->position.x, this->position.y - 20 }, 400);
		all_objects.add(bullet);
	}
}

void Player::update_collisions(int collider_index)
{
	//MAIN COLLIDER
	if (collider_index == 0)
	{
		for (int i = 0; i < collisions.size(); i++)
		{
			Object* object = collisions.element(i);
			if (object->type == Object_Type::ENEMY || object->type == Object_Type::NEUTRAL)
			{
				Entity* player = static_cast<Entity*>(object);
				float dx = position.x - player->position.x;
				float dy = position.y - player->position.y;
				float angle_between = atan2(dx, dy) * 180 / Helper::PI + 90;

				knockback_angle = 180 + angle_between;
				knockback = 0.5 * player->speed;

				if (angle == 90)
				{
					knockback = player->speed;
				}

			}
			else if (object->type == Object_Type::MAP_ELEMENT)
			{
				die();
			}
		}
	}
}

void Player::die()
{
	Dynamic_Array<int> distance;
	Dynamic_Array<int> width;
	Map_Manager::get_instance()->get_safe_area_to_spawn(distance, width, this);

	int new_x = (distance.element(0) + width.element(0) / 2) * 32;
	this->position.x = (float)new_x;
	this->speed = 0;
	this->angle = 90;
	this->knockback = 0;

	if (Helper::infinite_life_timer <= 0)
	{
		lives_left -= 1;
	}
}