#ifndef AI_VEHICLE_H
#define AI_VEHICLE_H

#include "Entity.h"

class AI_Vehicle : public Entity
{
public:
	static const int check_range;
	static int number_of_objects;
	Object_Type last_collision;
	Box_Collider* left_check;
	Box_Collider* right_check;
	
	AI_Vehicle(Object_Type type, const Vector2& position, float speed, SDL_Texture* texture);
	~AI_Vehicle();

	void update_collisions(int collider_index) override;

	void main_collider_collision(Object* collision);
	virtual void left_check_collision(Object* collision);
	virtual void right_check_collision(Object* collision);
};

#endif