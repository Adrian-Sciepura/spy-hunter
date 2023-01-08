#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Helper.h"
#include "Vector2.h"
#include "Input_Manager.h"
#include "Dynamic_String.h"
#include <cstdio>
#include "Asset_Manager.h"

class UI_Button
{
private:	
	SDL_Rect rect;
	SDL_Surface* surface;
	Dynamic_String text;

public:
	int id;
	Uint32 color;

	UI_Button(const Dynamic_String& text, Vector2 pos, int width, int height, int id);
	UI_Button(const UI_Button& source);
	~UI_Button();

	bool update(Input_Manager* input_manager);
	void draw();
	void on_hover();
	void change_text(const Dynamic_String& new_text);
};

#endif

