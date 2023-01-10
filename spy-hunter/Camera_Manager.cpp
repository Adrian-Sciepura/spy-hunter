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
	pos.x = 0;
	pos.y = 0;
	width = Helper::SCREEN_WIDTH;
	height = Helper::SCREEN_HEIGHT;
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
		float targetY = target->position.y - height / 2 - 100;
		pos.y += (targetY - pos.y) * 5.0f * Time_Manager::get_instance()->get_delta();
		//pos.y = targetY;
		//printf("Camera pos x: %d, y: %d\n", camera.x, camera.y);
	}
}

void Camera_Manager::set_target(Object* entity)
{
	this->target = entity;
	update();
	Map_Manager::get_instance()->last_camera_y_pos = pos.y;
}

Vector2 Camera_Manager::get_camera_pos()
{
	return { this->pos.x, this->pos.y };
}