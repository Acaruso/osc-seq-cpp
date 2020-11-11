#pragma once

#include <functional>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../store/ui_state.hpp"
#include "../store/coord.hpp"

void text_elt(
    std::string id,
    TTF_Font* font,
    std::string text,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click,
    std::function<void(int)> on_drag
);
