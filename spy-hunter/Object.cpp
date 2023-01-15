#include "Object.h"

Dynamic_Array<Object*> Object::all_objects = Dynamic_Array<Object*>();

void Object::cleanup()
{

	for (int i = all_objects.size() - 1; i >= 0; i--)
	{
		Object* object = all_objects.element(i);
		if(object->position.y > Helper::camera_pos.y + delete_range || 
			object->position.y < Helper::camera_pos.y - delete_range ||
			object->health <= 0)
		{
			delete all_objects.element(i);
			all_objects.remove(i);
		}
	}
}

Object::Object(Object_Type type, const Vector2& position, int width, int height, bool is_solid, SDL_Texture* texture)
{
	this->type = type;
	this->position = position;
	this->texture = texture;
	this->is_solid = is_solid;
	this->width = width;
	this->height = height;
	this->health = 100;
	this->all_collisions = 0;
	Box_Collider* collider = new Box_Collider{ width, height, true, {0.0f, 0.0f} };
	this->colliders.add(collider);
}

Object::Object(const Object& object) :
	Object(object.type, object.position, object.width, object.height, object.is_solid, object.texture)
{

}

Object::~Object()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		delete colliders.element(i);
	}
	colliders.clear();
}

void Object::update()
{

	for (int j = 0; j < colliders.size(); j++)
	{
		this->colliders.element(j)->update(this->position);
		for (int i = 0; i < all_objects.size(); i++)
		{
			if (all_objects.element(i) == this)
				continue;

			for (int k = 0; k < all_objects.element(i)->colliders.size(); k++)
			{
				if (this->colliders.element(j)->check_collision(*all_objects.element(i)->colliders.element(k)))
				{
					collisions.add(all_objects.element(i));
					all_collisions++;
				}
			}
		}

		if (collisions.size() > 0)
		{
			this->colliders.element(j)->is_colliding = true;
		}
		else
			this->colliders.element(j)->is_colliding = false;

		update_collisions(j);
		collisions.clear();
	}
	all_collisions = 0;
}

void Object::update_collisions(int collider_index)
{
	//IMPLEMENTATION IN CHILD CLASSES
}

void Object::draw()
{
	Vector2 relative_position
	{
		this->position.x,
		this->position.y - Helper::camera_pos.y
	};
	//printf("Player coords x: %f y: %f\n", relative_position.x / 32, relative_position.y / 32);

	if (texture != nullptr)
		Helper::render_texture(texture, relative_position.x, relative_position.y, nullptr);
	if (Box_Collider::show)
	{
		for (int i = 0; i < colliders.size(); i++)
			this->colliders.element(i)->draw(relative_position);
	}
}