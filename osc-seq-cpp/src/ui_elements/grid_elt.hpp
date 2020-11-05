#pragma once
#include <SDL.h>
#include "../store/grid.hpp"
#include "../store/ui_state.hpp"
#include <functional>

void do_grid(
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);
