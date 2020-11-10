#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_ttf.h>

#include "grid.hpp"
#include "rect.hpp"
#include "time_divisions.hpp"
#include "ui_state.hpp"

struct Store {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
	Ui_State ui_state;

	Rect rect;

    Seq_Grid seq_grid;

    int bpm;
    int clock;
    Time_Divisions time_divisions;

    std::unordered_map<std::string, SDL_Texture*> images;

    std::unordered_map<std::string, TTF_Font*> fonts;

    Store();
};
