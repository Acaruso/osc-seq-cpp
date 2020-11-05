#pragma once
#include <SDL.h>
#include "../store/grid.hpp"
#include "../store/ui_state.hpp"

void do_grid(Grid& grid, Ui_State& ui_state, SDL_Renderer* window_renderer);
