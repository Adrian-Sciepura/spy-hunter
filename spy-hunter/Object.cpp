#include "Object.h"

Object::Object(const Vector2& position, int width, int height, bool is_solid, SDL_Texture* texture)
{
	this->position = position;
	this->texture = texture;
	this->is_solid = is_solid;
	this->width = width;
	this->height = height;
	this->collider = { width, height, {0.0f, 0.0f} };
}

Object::Object(const Object& object) :
	Object(object.position, object.width, object.height, object.is_solid, object.texture)
{

}

void Object::update()
{
	//this->collider.update(position);
	//printf("test");
}

void Object::draw(const Vector2& camera_pos)
{
	Vector2 relaive_position
	{ 
		this->position.x - camera_pos.x,
		this->position.y - camera_pos.y
	};

	if (texture != nullptr)
		Helper::render_texture(texture, relaive_position.x, relaive_position.y, nullptr);
	if (Box_Collider::show)
		this->collider.draw();
	this->collider.update(relaive_position);

}