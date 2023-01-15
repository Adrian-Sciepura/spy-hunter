#ifndef NEUTRAL_H
#define NEUTRAL_H

#include "AI_Vehicle.h"
#include "Asset_Manager.h"

class Neutral : public AI_Vehicle
{
public:
	Neutral(const Vector2& position, float speed);

	void left_check_collision(Object* collision) override;
	void right_check_collision(Object* collision) override;
	void die() override;
};

#endif