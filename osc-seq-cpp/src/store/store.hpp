#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_FontCache.h>
#include <SDL_ttf.h>

#include "event_editor.hpp"
#include "grid.hpp"
#include "image.hpp"
#include "rect.hpp"
#include "time_divisions.hpp"
#include "ui_state.hpp"

struct Store
{
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;

	Ui_State ui_state;
    Ui_State prev_ui_state;

    Seq_Grid seq_grid;

    int bpm;
    int clock;
    Time_Divisions time_divisions;

    Event_Editor event_editor;

    std::unordered_map<std::string, Image_Set> images;

    // std::unordered_map<std::string, TTF_Font*> fonts;
    std::unordered_map<std::string, FC_Font*> fonts;

    Store();
};
