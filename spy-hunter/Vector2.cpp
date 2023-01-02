#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& source)
{
	this->x = source.x;
	this->y = source.y;
}

Vector2& Vector2::operator = (const Vector2& source)
{
	this->x = source.x;
	this->y = source.y;
	return *this;
}