#include "rect.hpp"
#include "../sdl/sdl_wrapper.hpp"

Rect::Rect() {}

Rect::Rect(int w, int h, int x, int y)
    : w(w), h(h), x(x), y(y) {
}

void do_rect(Rect& rect, Ui_State& ui_state, SDL_Renderer* window_renderer) {
    draw_rect(window_renderer, rect, true);
}
