#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Input_Manager.h"

class Player : public Entity
{
public:
	Player(const Vector2& position, int width, int height, bool is_solid, float max_speed, SDL_Texture* texture);

	void update_movement() override;
};

#endif