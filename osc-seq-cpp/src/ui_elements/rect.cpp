#include "rect.hpp"
#include "../sdl/sdl_wrapper.hpp"
#include "../util.hpp"

Rect::Rect() {}

Rect::Rect(int w, int h, int x, int y)
    : w(w), h(h), x(x), y(y) {
}

void do_rect(
    Rect& rect,
    bool toggled,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    if (is_clicked(rect, ui_state)) {
        on_click();
    }

    draw_rect(window_renderer, rect, toggled);
}
