#include "Helper.h"

const float Helper::PI = 3.1416;

//16:10 ASPECT RATIO RESOLUTION
const int Helper::SCREEN_WIDTH = 640;
const int Helper::SCREEN_HEIGHT = 400;
const int Helper::SCREEN_SCALE = 2;

SDL_Renderer* Helper::renderer = NULL;



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