#ifndef ENEMY_H
#define ENEMY_H

#include "AI_Vehicle.h"
#include "Asset_Manager.h"

class Enemy : public AI_Vehicle
{
public:
	Enemy(const Vector2& position, float speed);

	void left_check_collision(Object* collision) override;
	void right_check_collision(Object* collision) override;
	void die() override;
};

#endif