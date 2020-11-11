#pragma once

#include <functional>

#include <SDL.h>

#include "../store/rect.hpp"
#include "../store/ui_state.hpp"

void rect_elt(
    Rect& rect,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
);
