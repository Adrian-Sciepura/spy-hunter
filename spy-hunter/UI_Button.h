#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Helper.h"
#include "Vector2.h"
#include "Input_Manager.h"

class UI_Button
{
private:
	SDL_Rect rect;
	SDL_Color button_color;
	static Input_Manager* input_manager;
	static SDL_Rect mouse;

public:
	int id;

	UI_Button(Vector2 pos, int width, int height, int id);
	UI_Button(const UI_Button& source);
	~UI_Button();

	void update();
	void draw();
	void on_click();
	void on_hover();
};

#endif

