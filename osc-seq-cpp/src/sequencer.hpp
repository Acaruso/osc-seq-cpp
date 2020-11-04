#pragma once
#include <SDL.h>
#include <stdio.h>
#include "sdl/sdl_wrapper.hpp"
#include "store/store.hpp"

void loop(Store* store);
void do_grid(Grid& grid, Ui_State ui_state, SDL_Renderer* window_renderer);
bool is_coord_inside_rect(int x, int y, Rect rect);
