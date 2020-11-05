#pragma once
#include <SDL.h>
#include "ui_state.hpp"
#include "grid.hpp"
#include "../rect.hpp"

struct Store {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
	Ui_State ui_state;
	Rect rect;
    Grid grid;

    int bpm;
    int clock;

    Store();
};

Store* init_store();
