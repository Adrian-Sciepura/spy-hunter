#ifndef HELPER_H
#define HELPER_H

#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Dynamic_String.h"
#include "Vector2.h"

class Helper
{
public:
	static const float PI;
	static const int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_SCALE;
	static SDL_Renderer* renderer;

	static SDL_Texture* load_texture(const Dynamic_String& file, SDL_Renderer* renderer = Helper::renderer);
	static SDL_Surface* load_surface(const Dynamic_String& file, SDL_Renderer* renderer = Helper::renderer);
	static void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect destination, SDL_Rect* clip);
	static void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip);
};

#endif

