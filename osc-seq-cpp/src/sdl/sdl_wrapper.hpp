#pragma once
#include "../store/rect.hpp"
#include <SDL.h>
#include <string>

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 500;

struct Init_Sdl_Res {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
};

Init_Sdl_Res init_sdl();

void clear_window(SDL_Renderer* window_renderer);

void draw_rect(SDL_Renderer* window_renderer, Rect rect);

SDL_Texture* load_image(std::string path, SDL_Renderer* window_renderer);

SDL_Rect rect_to_sdl_rect(Rect rect);
