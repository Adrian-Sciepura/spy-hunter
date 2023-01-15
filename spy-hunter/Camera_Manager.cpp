#include "Camera_Manager.h"

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
	width = 640;
	height = 480;
	target = nullptr;
}

Camera_Manager::~Camera_Manager()
{

}


//-------------------------------


void Camera_Manager::update()
{
	if (target != nullptr)
	{
		if (target->health == 0)
		{
			target = nullptr;
			return;
		}
			
		float targetY = target->position.y - height / 2 - 100;
		Helper::camera_pos.y += (targetY - Helper::camera_pos.y) * 5.0f * Time_Manager::get_instance()->get_delta();
	}
}

void Camera_Manager::set_target(Object* entity)
{
	this->target = entity;
	update();
	Map_Manager::get_instance()->last_camera_y_pos = Helper::camera_pos.y;
}

Vector2 Camera_Manager::get_camera_pos()
{
	return { Helper::camera_pos.x, Helper::camera_pos.y };
}