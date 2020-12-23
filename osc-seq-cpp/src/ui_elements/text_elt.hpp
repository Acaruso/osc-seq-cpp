#pragma once

#include <functional>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../store/coord.hpp"
#include "../store/store.hpp"

void text_elt(std::string text, Coord& coord, Store& store, int z_coord = 1);

void text_elt(std::string text, FC_Font* font, Coord& coord, Store& store, int z_coord = 1);

void text_elt_draggable(
    std::string id,
    std::string text,
    Coord& coord,
    Store& store,
    std::function<void()> on_click,
    std::function<void(int)> on_drag
);
