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

	static SDL_Color color_creator(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	static SDL_Rect rectangle_creator(int x, int y, int w, int h);

	static const SDL_Color gray;
	static const SDL_Color light_gray;
	static const SDL_Color black;
	static const SDL_Color red;


	static SDL_Texture* load_texture(const Dynamic_String& file, SDL_Renderer* renderer = Helper::renderer);
	static SDL_Surface* load_surface(const Dynamic_String& file, SDL_Renderer* renderer = Helper::renderer);
	static void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect destination, SDL_Rect* clip);
	static void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip);
	static void render_rectangle(SDL_Renderer* renderer, const SDL_Rect* rectangle, const SDL_Color& color, bool filled = false);
};

#endif

