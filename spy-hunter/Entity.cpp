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

Entity::Entity(SDL_Texture* texture, const Vector2& position)
{
	this->position = position;
	this->texture = texture;
	this->collider = new Box_Collider({ 50, 80 }, { 0, 0 });

	entities[number_of_entities] = this;
	number_of_entities++;
}

void Entity::draw()
{
	Helper::render_texture(this->texture, Helper::renderer, this->position.x, this->position.y, nullptr);
	this->collider->update(this->position);
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
