#pragma once
#include <SDL.h>
#include "../store/ui_state.hpp"

struct Rect {
    int w;
    int h;
    int x;
    int y;
    Rect();
    Rect(int w, int h, int x, int y);
};

void do_rect(Rect& rect, Ui_State& ui_state, SDL_Renderer* window_renderer);
