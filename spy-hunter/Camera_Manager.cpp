#include "Camera_Manager.h"

//SINGLETON DESIGN PATTERN

Camera_Manager* Camera_Manager::instance = nullptr;

Camera_Manager* Camera_Manager::get_instance()
{
	if (instance == nullptr)
		instance = new Camera_Manager();
	return instance;
}

void Camera_Manager::destroy_instance()
{
	if (instance == nullptr)
		return;
	delete instance;
	instance = nullptr;
}

Camera_Manager::Camera_Manager()
{
	camera.x = 0;
	camera.y = 0;
	camera.w = Helper::SCREEN_WIDTH;
	camera.h = Helper::SCREEN_HEIGHT;

	target = nullptr;
}


//CLASS CONTENT

void Camera_Manager::update()
{
	if (target != nullptr)
	{
		float targetY = target->position.y - camera.h / 2;
		//camera.y += (targetY - camera.y) * 2.6f * Time_Manager::get_instance()->get_delta();
		camera.y = targetY;
	}
}

void Camera_Manager::set_target(Object* entity)
{
	this->target = entity;
}

Vector2 Camera_Manager::get_camera_pos()
{
	return { (float)this->camera.x, (float)this->camera.y };
}