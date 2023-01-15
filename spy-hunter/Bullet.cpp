#include "Bullet.h"

Bullet::Bullet(const Vector2& position, float speed) :
	Entity(Object_Type::BULLET, position, 5, 10, true, 300, Asset_Manager::get_instance()->bullet_texture)
{
	this->speed = speed;
}

void Bullet::update_movement()
{
	if (total_distance > 240)
		health = 0;

	Entity::update_movement();
}
