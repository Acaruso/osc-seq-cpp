#pragma once
#include "../store/ui_state.hpp"
#include <SDL.h>
#include <functional>

struct Rect {
    int w;
    int h;
    int x;
    int y;
    Rect();
    Rect(int w, int h, int x, int y);
};

void do_rect(
    Rect& rect,
    bool toggled,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);
