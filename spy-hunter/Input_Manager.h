#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Vector2.h"
#include "Helper.h"
#include <cstdio>

class Input_Manager
{
private:
	static Input_Manager* instance;

	int number_of_keys;
	const Uint8* keyboard_state;
	Uint8* previous_keyboard_state;

	Uint32 mouse_state;
	Uint32 previous_mouse_state;

	Vector2 mouse_pos;
	SDL_Rect mouse_box;

	Input_Manager();
	~Input_Manager();
	
public:
	static Input_Manager* get_instance();
	static void destroy_instance();

	void update_keyboard();
	bool key_pressed(SDL_Scancode key);
	bool key_released(SDL_Scancode key);

	void update_mouse();
	bool mouse_button_pressed();
	bool mouse_button_released();

	Vector2 get_mouse_pos();
	SDL_Rect get_mouse_box();
};

#endif