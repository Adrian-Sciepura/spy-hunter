#include "Neutral.h"

Neutral::Neutral(const Vector2& position, float speed) :
	AI_Vehicle(Object_Type::NEUTRAL, position, speed, Asset_Manager::get_instance()->neutral_texture)
{

}

void Neutral::left_check_collision(Object* collision)
{
	if (collision->type == MAP_ELEMENT)
	{
			angle = 70;
	}
}

void Neutral::right_check_collision(Object* collision)
{
	if (collision->type == MAP_ELEMENT)
	{
			angle = 110;
	}
}

void Neutral::die()
{
	health = 0;

	if (last_collision == Object_Type::PLAYER || last_collision == Object_Type::BULLET)
		Helper::score_freeze_time = 2.5f;
}