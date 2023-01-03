#include "Entity.h"

Entity** Entity::entities = nullptr;
int Entity::number_of_entities = 0;


Entity** Entity::get_all_entities()
{
	if (entities == nullptr)
		entities = (Entity**)malloc(20 * sizeof(Entity));

	return entities;
}

int Entity::get_number_of_entities()
{
	return number_of_entities;
}

void Entity::remove_all_entities()
{
	if (entities == nullptr)
		return;

	for (int i = 0; i < number_of_entities; i++)
		delete entities[i];

	free(entities);
}

Entity::Entity(SDL_Texture* texture, const Vector2& position, float max_speed)
{
	this->position = position;
	this->texture = texture;
	this->collider = new Box_Collider({ 50, 80 }, { 0, 0 });
	this->speed = 0;
	this->max_speed = max_speed;
	this->angle = 90;
	this->is_moving = false;

	entities[number_of_entities] = this;
	number_of_entities++;
}

void Entity::draw(const Vector2& camera_pos)
{
	Vector2 relaive_position 
	{	this->position.x - camera_pos.x, 
		this->position.y - camera_pos.y
	};

	Helper::render_texture(this->texture, Helper::renderer, relaive_position.x, relaive_position.y, nullptr);
	this->collider->update(relaive_position);
}

void Entity::update_collisions()
{
	int how_many_colliders = 0;
	for (int i = 0; i < number_of_entities; i++)
	{
		if (entities[i] == this)
			continue;

		if (this->collider->check_collision(*(entities[i]->collider)))
			how_many_colliders++;
	}

	if (how_many_colliders > 0)
		this->collider->is_colliding = true;
	else
		this->collider->is_colliding = false;
}

void Entity::update_movement()
{
	Input_Manager* input_manager = Input_Manager::get_instance();

	if(!input_manager->key_pressed(SDL_SCANCODE_UP) && speed == 0)
		is_moving = false;

	if (input_manager->key_pressed(SDL_SCANCODE_UP))
	{
		is_moving = true;
		if (input_manager->key_pressed(SDL_SCANCODE_LEFT))
			angle = 135;
		else if (input_manager->key_pressed(SDL_SCANCODE_RIGHT))
			angle = 45;
		else
			angle = 90;
	}
	else if (input_manager->key_pressed(SDL_SCANCODE_DOWN))
	{
		angle = 270;
	}
	else if (is_moving)
	{
		if (input_manager->key_pressed(SDL_SCANCODE_LEFT))
			angle = 135;
		else if (input_manager->key_pressed(SDL_SCANCODE_RIGHT))
			angle = 45;
		else
			angle = 90;
	}



	if(is_moving)
	{
		float move_dist = speed * Time_Manager::get_instance()->get_delta() * 4.0;
		float x_move = move_dist * cos((angle * Helper::PI) / 180.0);
		float y_move = move_dist * -sin((angle * Helper::PI) / 180.0);

		if (y_move > 0)
		{
			speed -= 1;
			y_move = -y_move;
		}
		else
		{
			if ((speed + 1) <= max_speed)
				speed += 1;
		}



		//if (angle == 270 && (speed - 0.5) >= 0)
		//{
		//	speed -= 0.5;
		//	return;
		//}
		//else if ((speed + 0.5) <= max_speed)
		//	speed += 0.5;

		
		position += {x_move, y_move};
	}

}