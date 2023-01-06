#include "Helper.h"

const float Helper::PI = 3.1416;

//4:3 ASPECT RATIO RESOLUTION
const int Helper::SCREEN_WIDTH = 640;
const int Helper::SCREEN_HEIGHT = 480;
const int Helper::SCREEN_SCALE = 2;

SDL_Renderer* Helper::renderer = NULL;


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


SDL_Texture* Helper::load_texture(const Dynamic_String& file, SDL_Renderer* renderer)
{
	SDL_Surface* tmp = SDL_LoadBMP(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmp);
	return texture;
}

SDL_Surface* Helper::load_surface(const Dynamic_String& file, SDL_Renderer* renderer)
{
	return nullptr;
}

void Helper::render_texture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect destination, SDL_Rect* clip)
{
	SDL_RenderCopy(renderer, texture, clip, &destination);
}

void Helper::render_texture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip)
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
	render_texture(texture, renderer, dst, clip);
}

void Helper::render_rectangle(SDL_Renderer* renderer, const SDL_Rect* rectangle, const SDL_Color& color, bool filled)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	if (filled)
		SDL_RenderFillRect(renderer, rectangle);
	else
		SDL_RenderDrawRect(renderer, rectangle);
}