#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_FontCache.h>
#include <SDL_ttf.h>

#include "event_editor.hpp"
#include "grid/grid.hpp"
#include "grid/pattern_grid.hpp"
#include "grid/seq_grid.hpp"
#include "image.hpp"
#include "rect.hpp"
#include "time_divisions.hpp"
#include "ui_state.hpp"

enum Transport_Mode
{
    Play,
    Pause
};

struct Store
{
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;

	Ui_State ui_state;
    Ui_State prev_ui_state;

    Seq_Grid seq_grid;

    Pattern_Grid pattern_grid;

    Grid_Cell copied_cell;

    int bpm;
    int clock;
    int blink_clock;
    Time_Divisions time_divisions;

    Transport_Mode transport_mode;

    Event_Editor event_editor;

    std::unordered_map<std::string, Image_Set> images;

    int font_size;
    int font_width;
    int line_height;

    std::unordered_map<std::string, FC_Font*> fonts;

    Store();
};
