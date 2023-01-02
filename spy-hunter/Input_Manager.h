#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"

class Input_Manager
{
private:
	static Input_Manager* instance;
	const Uint8* keyboard_state;

public:
	static Input_Manager* get_instance();
	static void destroy_instance();
	void update();
	bool key_pressed(SDL_Scancode key);
};

#endif

