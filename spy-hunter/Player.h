#ifndef PLAYER_H
#define PLAYER_H

#include "Asset_Manager.h"
#include "Map_Manager.h"
#include "Input_Manager.h"

#include "Bullet.h"
#include "Entity.h"

class Player : public Entity
{
public:
	int lives_left;

	Player(const Vector2& position, int width, int height, bool is_solid, float max_speed, SDL_Texture* texture);

	void update_movement() override;
	void update_collisions(int collider_index) override;
	void die() override;
};

#endif