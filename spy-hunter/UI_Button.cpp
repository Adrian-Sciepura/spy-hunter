#include "UI_Button.h"

Input_Manager* UI_Button::input_manager = Input_Manager::get_instance();
SDL_Rect UI_Button::mouse = Helper::rectangle_creator(1, 1, 1, 1);

UI_Button::UI_Button(Vector2 pos, int width, int height, int id)
{
	button_color = Helper::gray;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = width;
	rect.h = height;
	this->id = id;
}

UI_Button::UI_Button(const UI_Button& source)
{
	button_color = Helper::gray;
	this->rect = source.rect;
	id = source.id;
}

UI_Button::~UI_Button()
{

}

void UI_Button::draw()
{
	Helper::render_rectangle(Helper::renderer, &rect, button_color, true);
}


void UI_Button::update()
{
	Vector2 pos = input_manager->get_mouse_pos();
	mouse.x = pos.x;
	mouse.y = pos.y;

	if (SDL_HasIntersection(&rect, &mouse))
	{
		on_hover();
		bool clicked = input_manager->mouse_button_pressed();
		if (clicked)
		{
			on_click();
		}
	}
	else
	{
		button_color = Helper::gray;
	}
}

void UI_Button::on_click()
{
	button_color = Helper::red;
}

void UI_Button::on_hover()
{
	button_color = Helper::light_gray;
}