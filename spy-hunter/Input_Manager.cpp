#include "Input_Manager.h"

Input_Manager* Input_Manager::instance = nullptr;

Input_Manager* Input_Manager::get_instance()
{
	if (instance == nullptr)
		instance = new Input_Manager();
	
	return instance;
}

void Input_Manager::destroy_instance()
{
	if (instance == nullptr)
		return;

	delete instance;
	instance = nullptr;
}

void Input_Manager::update_keyboard()
{
	keyboard_state = SDL_GetKeyboardState(NULL);
}

bool Input_Manager::key_pressed(SDL_Scancode key)
{
	return (keyboard_state[key] != 0);
}

void Input_Manager::update_mouse()
{
	int temp_x;
	int temp_y;
	mouse_state = SDL_GetMouseState(&temp_x, &temp_y);
	mouse_pos = { (float)temp_x/Helper::SCREEN_SCALE, (float)temp_y/Helper::SCREEN_SCALE };
}

bool Input_Manager::mouse_button_pressed()
{
	Uint32 mask = SDL_BUTTON_LMASK;
	return (mouse_state & mask) != 0;
}

Vector2 Input_Manager::get_mouse_pos()
{
	return mouse_pos;
}