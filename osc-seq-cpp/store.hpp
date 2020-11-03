#pragma once
#include <SDL.h>

struct Store {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
};

Store* init_store();
