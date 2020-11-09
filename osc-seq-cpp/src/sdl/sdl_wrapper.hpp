#pragma once
#include "../store/rect.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Init_Sdl_Res {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
};

Init_Sdl_Res init_sdl();

void clear_window(SDL_Renderer* window_renderer);

void draw_rect(SDL_Renderer* window_renderer, Rect rect);

SDL_Texture* load_image(std::string path, SDL_Renderer* window_renderer);
