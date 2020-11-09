#pragma once
#include "../store/grid.hpp"
#include "../store/ui_state.hpp"
#include <SDL.h>
#include <functional>

void grid_elt(
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);

void grid_elt_clickable(
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);

void grid_for_each(Grid& grid, std::function<void(Grid_Cell&, int, int)> fn);
