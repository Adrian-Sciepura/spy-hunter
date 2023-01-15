#include "Box_Collider.h"

bool Box_Collider::show = false;

Box_Collider::Box_Collider()
{
	this->box.x = 0;
	this->box.y = 0;
	this->box.w = 0;
	this->box.h = 0;
	this->is_colliding = false;
	this->is_trigger = true;
	this->offset = { 0,0 };
}

Box_Collider::Box_Collider(int width, int height, bool is_trigger, const Vector2& offset)
{
	this->offset = offset;
	this->box.x = 0;
	this->box.y = 0;
	this->box.w = width;
	this->box.h = height;
	this->is_trigger = is_trigger;
	this->is_colliding = false;
}

Box_Collider::Box_Collider(const Box_Collider& collider) :
	Box_Collider(collider.box.w, collider.box.h, collider.is_trigger, collider.offset)
{

}


void Box_Collider::update(const Vector2& object_pos)
{
	this->box.x = object_pos.x + offset.x;
	this->box.y = object_pos.y + offset.y;
}

void Box_Collider::draw(const Vector2& pos)
{
	if(this->is_colliding == false)
		SDL_SetRenderDrawColor(Helper::renderer, 0, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(Helper::renderer, 255, 0, 0, 255);

	SDL_Rect temp = { pos.x + offset.x, pos.y + offset.y, this->box.w, this->box.h };
	SDL_RenderDrawRect(Helper::renderer, &temp);
}

bool Box_Collider::check_collision(const Box_Collider& collider)
{
	SDL_Rect result;
	if (collider.is_trigger == false)
		return false;

	if (SDL_IntersectRect(&this->box, &collider.box, &result))
		return true;
	
	return false;
}

