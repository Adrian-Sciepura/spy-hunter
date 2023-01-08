#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "Object.h"
#include "Time_Manager.h"
#include "Helper.h"
#include "Vector2.h"

class Camera_Manager
{
private:
	static Camera_Manager* instance;
	Object* target;
	SDL_Rect camera;
	
	Camera_Manager();

public:
	static Camera_Manager* get_instance();
	static void destroy_instance();
	
	void update();
	void set_target(Object* entity);
	Vector2 get_camera_pos();
	//Entity* get_target();
};

#endif