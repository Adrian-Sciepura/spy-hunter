#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Vector2.h"
#include "Helper.h"

class Input_Manager
{
private:
	static Input_Manager* instance;
	const Uint8* keyboard_state;
	Uint32 mouse_state;
	Vector2 mouse_pos;
	
public:
	static Input_Manager* get_instance();
	static void destroy_instance();

	void update_keyboard();
	bool key_pressed(SDL_Scancode key);

	void update_mouse();
	bool mouse_button_pressed();
	Vector2 get_mouse_pos();
};

#endif

