#include "rect_elt.hpp"
#include "../sdl/sdl_wrapper.hpp"
#include "../util.hpp"

void rect_elt(
    Rect& rect,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    if (is_mouseup(rect, ui_state)) {
        on_click();
    }

    draw_rect(window_renderer, rect);
}
