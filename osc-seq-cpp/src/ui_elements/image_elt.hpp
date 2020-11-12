#pragma once

#include <functional>

#include <SDL.h>

#include "../store/coord.hpp"
#include "../store/image_set.hpp"
#include "../store/ui_state.hpp"

void image_elt(
    Image_Set image_set,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);

void image_elt_clickable(
    Image_Set image_set,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);

void image_elt_clickable_toggleable(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);

void image_elt_toggleable(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    SDL_Renderer* window_renderer
);
