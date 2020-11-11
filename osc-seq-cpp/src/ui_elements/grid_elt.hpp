#pragma once

#include <functional>

#include <SDL.h>

#include "../store/coord.hpp"
#include "../store/grid.hpp"
#include "../store/ui_state.hpp"

void grid_elt(
    Coord coord,
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);

void grid_elt_clickable(
    Coord coord,
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);

void grid_for_each(Grid& grid, std::function<void(Grid_Cell&, int, int)> fn);
