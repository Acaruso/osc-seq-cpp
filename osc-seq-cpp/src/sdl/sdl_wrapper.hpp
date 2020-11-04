#pragma once
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Init_sdl_res {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
};

Init_sdl_res* init_sdl();

void clear_window(SDL_Renderer* window_renderer);
