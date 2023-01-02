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

void Input_Manager::update()
{
	keyboard_state = SDL_GetKeyboardState(NULL);
}

bool Input_Manager::key_pressed(SDL_Scancode key)
{
	return keyboard_state[key];
}