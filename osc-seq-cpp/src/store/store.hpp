#pragma once
#include <SDL.h>
#include "ui_state.hpp"
#include "grid.hpp"

struct Store {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
	Ui_State ui_state;
	SDL_Rect rect;
    Grid grid;

    Store();
};

Store* init_store();
