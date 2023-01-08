#include "Box_Collider.h"

bool Box_Collider::show = true;

Box_Collider::Box_Collider()
{
	this->box.x = 0;
	this->box.y = 0;
	this->box.w = 0;
	this->box.h = 0;
	this->is_colliding = false;
	this->offset = { 0,0 };
}

Box_Collider::Box_Collider(int width, int height, const Vector2& offset)
{
	this->offset = offset;
	this->box.x = 0;
	this->box.y = 0;
	this->box.w = width;
	this->box.h = height;
	this->is_colliding = false;
}

Box_Collider::Box_Collider(const Box_Collider& collider) :
	Box_Collider(collider.box.w, collider.box.h, collider.offset)
{

}


void Box_Collider::update(const Vector2& object_pos)
{
	this->box.x = object_pos.x + offset.x;
	this->box.y = object_pos.y + offset.y;
}

void Box_Collider::draw()
{
	if(this->is_colliding == false)
		SDL_SetRenderDrawColor(Helper::renderer, 0, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(Helper::renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(Helper::renderer, &this->box);
}

bool Box_Collider::check_collision(const Box_Collider& collider)
{
	SDL_Rect result;

	if (SDL_IntersectRect(&this->box, &collider.box, &result))
		return true;
	
	return false;
}

