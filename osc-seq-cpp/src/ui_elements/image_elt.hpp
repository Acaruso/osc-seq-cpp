#pragma once

#include <functional>

#include <SDL.h>

#include "../store/coord.hpp"
#include "../store/ui_state.hpp"

void image_elt(
    SDL_Texture* image,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);
