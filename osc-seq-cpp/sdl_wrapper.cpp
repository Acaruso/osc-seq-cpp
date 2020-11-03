#include "sdl_wrapper.hpp"

Init_sdl_res* init_sdl() {
	Init_sdl_res* res = new Init_sdl_res;

	SDL_Init(SDL_INIT_VIDEO);

	res->window = SDL_CreateWindow(
		"title", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		SDL_WINDOW_SHOWN
	);

	res->window_surface = SDL_GetWindowSurface(res->window);
	res->window_renderer = SDL_CreateRenderer(res->window, -1, SDL_RENDERER_ACCELERATED);

	return res;
}
