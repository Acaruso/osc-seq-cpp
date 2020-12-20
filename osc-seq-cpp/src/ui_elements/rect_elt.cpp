#include "rect_elt.hpp"

#include "../sdl/sdl_wrapper.hpp"
#include "../util.hpp"

void rect_elt(
    Rect& rect,
    Color& color,
    Store& store
) {
    draw_rect(rect, color, store.window_renderer);
}

void rect_elt_clickable(
    Rect& rect,
    Color& color,
    Store& store,
    std::function<void()> on_click
) {
    if (is_mouseup_event_inside_rect(rect, store.ui_state, store.prev_ui_state)) {
        on_click();
    }

    draw_rect(rect, color, store.window_renderer);
}
