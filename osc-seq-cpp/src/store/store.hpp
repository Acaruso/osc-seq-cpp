#pragma once
#include <SDL.h>
#include "ui_state.hpp"
#include "grid.hpp"
#include "../ui_elements/rect.hpp"

struct Time_Divisions {
    int n4;
    int n8;
    int n16;
    int n2;
    int n1;
    int n12;
    int n6;
    int n3;
};

struct Store {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
	Ui_State ui_state;
	Rect rect;
    Grid grid;

    int bpm;
    int clock;
    Time_Divisions time_divisions;

    Store();
};
