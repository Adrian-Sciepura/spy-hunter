#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "Asset_Manager.h"

class Bullet : public Entity
{
public:
	Bullet(const Vector2& position, float speed);

	void update_movement() override;
};

#endif