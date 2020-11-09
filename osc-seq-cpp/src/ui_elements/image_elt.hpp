#pragma once
#include "../store/ui_state.hpp"
#include "../store/coord.hpp"
#include <SDL.h>
#include <functional>

void image_elt(
    SDL_Texture* image,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);
