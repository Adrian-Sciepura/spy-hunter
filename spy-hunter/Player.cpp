#include "Player.h"

Player::Player(const Vector2& position, int width, int height, bool is_solid, float max_speed, SDL_Texture* texture) :
	Entity(position, width, height, is_solid, max_speed, texture)
{

}

void Player::update_movement()
{
	Input_Manager* input = Input_Manager::get_instance();

	if (!input->key_pressed(SDL_SCANCODE_UP) && speed == 0)
		is_moving = false;

	if (input->key_pressed(SDL_SCANCODE_UP))
	{
		is_moving = true;

		speed += 0.5;
		if (input->key_pressed(SDL_SCANCODE_LEFT))
			angle = 135;
		else if (input->key_pressed(SDL_SCANCODE_RIGHT))
			angle = 45;
		else
			angle = 90;
	}
	else if (input->key_pressed(SDL_SCANCODE_DOWN))
	{
		speed -= 0.5;
	}
	else if (is_moving)
	{
		if (input->key_pressed(SDL_SCANCODE_LEFT))
			angle = 135;
		else if (input->key_pressed(SDL_SCANCODE_RIGHT))
			angle = 45;
		else
			angle = 90;
	}

	Entity::update_movement();
}