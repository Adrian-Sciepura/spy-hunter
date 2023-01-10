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

Input_Manager::Input_Manager()
{
	mouse_state = 0;
	previous_mouse_state = 0;
	mouse_pos = { 0,0 };
	mouse_box.w = 1;
	mouse_box.h = 1;
	mouse_box.x = 0;
	mouse_box.y = 0;
}

Input_Manager::~Input_Manager()
{

}


//--------------------------------------


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
	previous_mouse_state = mouse_state;
	mouse_state = SDL_GetMouseState(&temp_x, &temp_y);
	mouse_pos = { (float)temp_x/Helper::SCREEN_SCALE, (float)temp_y/Helper::SCREEN_SCALE };
	mouse_box.x = mouse_pos.x;
	mouse_box.y = mouse_pos.y;
}

bool Input_Manager::mouse_button_pressed()
{
	return (mouse_state & SDL_BUTTON_LMASK) != 0;
}

bool Input_Manager::mouse_button_released()
{
	return ((previous_mouse_state & SDL_BUTTON_LMASK) != 0) && ((mouse_state & SDL_BUTTON_LMASK) == 0);
}

Vector2 Input_Manager::get_mouse_pos()
{
	return mouse_pos;
}

SDL_Rect Input_Manager::get_mouse_box()
{
	return mouse_box;
}