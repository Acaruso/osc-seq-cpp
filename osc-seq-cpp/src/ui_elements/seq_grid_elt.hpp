#pragma once
#include "../store/grid.hpp"
#include "../store/ui_state.hpp"
#include "grid_elt.hpp"
#include <SDL.h>
#include <functional>

void seq_grid_elt(
    Seq_Grid& seq_grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);