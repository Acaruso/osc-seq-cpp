#pragma once
#include "../store/ui_state.hpp"
#include "../store/rect.hpp"
#include <SDL.h>
#include <functional>

void rect_elt(
    Rect& rect,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);
