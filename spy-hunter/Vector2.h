#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	float x, y;

	Vector2(float x = 0, float y = 0);
	Vector2(const Vector2& source);

	//void translate(const Vector2& vector);

	Vector2& operator = (const Vector2& source);
	friend Vector2 operator + (const Vector2& first_element, const Vector2& second_element);
	Vector2& operator += (const Vector2& vector);
	//friend Vector2 operator + (const Vector2& first_element, int number);
	friend Vector2 operator - (const Vector2& first_element, const Vector2& second_element);
	Vector2& operator -= (const Vector2& vector);
	//friend Vector2 operator - (const Vector2& first_element, int number);
};

#endif
