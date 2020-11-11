#pragma once

#include <functional>

#include <SDL.h>

#include "../store/coord.hpp"
#include "../store/grid.hpp"
#include "../store/ui_state.hpp"
#include "grid_elt.hpp"

void seq_grid_elt(
    Coord coord,
    Seq_Grid& seq_grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);
