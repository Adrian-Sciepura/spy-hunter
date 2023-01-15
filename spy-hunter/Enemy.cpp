#include "Enemy.h"

Enemy::Enemy(const Vector2& position, float speed) :
	AI_Vehicle(Object_Type::ENEMY, position, speed, Asset_Manager::get_instance()->enemy_texture)
{

}

void Enemy::left_check_collision(Object* collision)
{
	if (collision->type == PLAYER)
	{
		angle = 110;
	}
	else if (collision->type == MAP_ELEMENT)
	{
		angle = 70;
	}
}

void Enemy::right_check_collision(Object* collision)
{
	if (collision->type == PLAYER)
	{
		angle = 70;
	}
	else if (collision->type == MAP_ELEMENT)
	{
		angle = 110;
	}
}

void Enemy::die()
{
	health = 0;

	if (last_collision == Object_Type::PLAYER || last_collision == Object_Type::BULLET)
		if (Helper::score_freeze_time <= 0)
			Helper::score += 150;
}