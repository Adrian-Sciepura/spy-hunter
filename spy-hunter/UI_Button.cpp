#include "UI_Button.h"

UI_Button::UI_Button(const Dynamic_String& text, Vector2 pos, int width, int height, int id)
{
	surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	this->text = text;
	color = SDL_MapRGB(surface->format, 150, 149, 153);
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = width;
	rect.h = height;
	this->id = id;
}

UI_Button::UI_Button(const UI_Button& source)
{
	surface = SDL_CreateRGBSurface(0, source.rect.w, source.rect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	color = SDL_MapRGB(surface->format, 150, 149, 153);
	this->rect = source.rect;
	this->text = source.text;
	id = source.id;
}

UI_Button::~UI_Button()
{
	SDL_FreeSurface(surface);
}

void UI_Button::draw()
{
	SDL_FillRect(surface, NULL, color);
	Helper::render_text(Asset_Manager::get_instance()->font, surface, this->text, true);
	Helper::render_surface(surface, rect.x, rect.y);
}

bool UI_Button::update(Input_Manager* input_manager)
{
	SDL_Rect m = input_manager->get_mouse_box();
	if (SDL_HasIntersection(&rect, &m))
	{
		on_hover();
		bool clicked = input_manager->mouse_button_released();
		if (clicked)
		{
			return true;
		}
	}
	else
	{
		color = SDL_MapRGB(surface->format, 150, 149, 153);
	}
	return false;
}

void UI_Button::on_hover()
{
	color = SDL_MapRGB(surface->format, 204, 203, 205);
}

void UI_Button::change_text(const Dynamic_String& new_text)
{
	this->text = new_text;
}