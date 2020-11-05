#include "rect.hpp"
#include "../sdl/sdl_wrapper.hpp"

Rect::Rect() {}

Rect::Rect(int w, int h, int x, int y)
    : w(w), h(h), x(x), y(y) {
}

void do_rect(Rect& rect, Ui_State& ui_state, SDL_Renderer* window_renderer) {
    int movement_amount = 3;

    // if (store.ui_state.click) {
    // 	store.rect.x = store.ui_state.x;
    // 	store.rect.y = store.ui_state.y;
    // }

    if (ui_state.up) {
        rect.y -= movement_amount;
    }
    if (ui_state.down) {
        rect.y += movement_amount;
    }
    if (ui_state.right) {
        rect.x += movement_amount;
    }
    if (ui_state.left) {
        rect.x -= movement_amount;
    }

    draw_rect(window_renderer, rect, true);
}
