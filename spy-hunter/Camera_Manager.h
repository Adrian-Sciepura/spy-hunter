#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "Entity.h"
#include "Time_Manager.h"
#include "Helper.h"
#include "Vector2.h"

class Camera_Manager
{
private:
	static Camera_Manager* instance;
	Entity* target;
	SDL_Rect camera;

	Camera_Manager();

public:
	static Camera_Manager* get_instance();
	static void destroy_instance();
	
	void update();
	void set_target(Entity* entity);
	Vector2 get_camera_pos();
	//Entity* get_target();
};

#endif