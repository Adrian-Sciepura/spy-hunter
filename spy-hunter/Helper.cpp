#include "Helper.h"

SDL_Renderer* Helper::renderer = NULL;
SDL_Window* Helper::window = NULL;
Vector2 Helper::camera_pos = {};

int Helper::score = 0;
float Helper::score_freeze_time = 0.0f;
float Helper::infinite_life_timer = 30.0f;

SDL_Color Helper::color_creator(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

SDL_Rect Helper::rectangle_creator(int x, int y, int w, int h)
{
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	return rectangle;
}

const SDL_Color Helper::gray = Helper::color_creator(150, 149, 153);
const SDL_Color Helper::light_gray = Helper::color_creator(204, 203, 205);
const SDL_Color Helper::black = Helper::color_creator(0, 0, 0);
const SDL_Color Helper::red = Helper::color_creator(255, 0, 0);


SDL_Texture* Helper::load_texture(const Dynamic_String& file)
{
	SDL_Surface* tmp = SDL_LoadBMP(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return texture;
}

SDL_Surface* Helper::load_surface(const Dynamic_String& file)
{
	return nullptr;
}

void Helper::render_texture(SDL_Texture* texture, SDL_Rect destination, SDL_Rect* clip)
{
	SDL_RenderCopy(Helper::renderer, texture, clip, &destination);
}

void Helper::render_texture(SDL_Texture* texture, int x, int y, SDL_Rect* clip)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	}
	render_texture(texture, dst, clip);
}

void Helper::render_rectangle(const SDL_Rect* rectangle, const SDL_Color& color, bool filled)
{
	SDL_SetRenderDrawColor(Helper::renderer, color.r, color.g, color.b, color.a);
	if (filled)
		SDL_RenderFillRect(Helper::renderer, rectangle);
	else
		SDL_RenderDrawRect(Helper::renderer, rectangle);
}

void Helper::render_text(SDL_Surface* font, SDL_Surface* surface, const Dynamic_String& text, bool centered)
{
	const char* temp = text;
	int x = 10;
	int y = 10;
	if (centered)
	{
		x = (surface->w - text.length())/4;
		y = (surface->h - 8)/2;
	}
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;

	while (*temp) 
	{
		c = *temp & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(font, &s, surface, &d);
		x += 8;
		temp++;
	};
}

void Helper::render_surface(SDL_Surface* surface, int x, int y)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	render_texture(texture, x, y, nullptr);
	SDL_DestroyTexture(texture);
}

void Helper::draw_line(int x1, int y1, int x2, int y2, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.a, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}