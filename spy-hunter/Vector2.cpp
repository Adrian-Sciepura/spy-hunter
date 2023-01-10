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


//OPERATOR OVERLOADING

Vector2& Vector2::operator = (const Vector2& source)
{
	this->x = source.x;
	this->y = source.y;
	return *this;
}

Vector2 operator + (const Vector2& first_element, const Vector2& second_element)
{
	Vector2 vector
	{
		first_element.x + second_element.x,
		first_element.y + second_element.y
	};
	return vector;
}

Vector2& Vector2::operator += (const Vector2& vector)
{
	this->x += vector.x;
	this->y += vector.y;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;
	return *this;
}

bool operator == (const Vector2& first_vector, const Vector2& second_vector)
{
	if (first_vector.x != second_vector.x)
		return false;
	if (first_vector.y != second_vector.y)
		return false;

	return true;
}

Vector2 operator - (const Vector2& first_element, const Vector2& second_element)
{
	return Vector2 {first_element.x - second_element.x, first_element.y - second_element.y};
}