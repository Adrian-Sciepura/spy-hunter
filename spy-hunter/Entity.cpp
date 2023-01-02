#include "Entity.h"

Entity::Entity(SDL_Texture* texture)
{
	this->texture = texture;
}

void Entity::draw()
{
	Helper::render_texture(this->texture, Helper::renderer, this->position.x, this->position.y, nullptr);
}