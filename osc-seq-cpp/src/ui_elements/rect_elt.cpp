#include "rect_elt.hpp"

#include "../sdl/sdl_wrapper.hpp"
#include "../util.hpp"

void rect_elt(
    Rect& rect,
    Store& store,
    std::function<void()> on_click
) {
    if (is_mouseup_event_inside_rect(rect, store.ui_state, store.prev_ui_state)) {
        on_click();
    }

    draw_rect(store.window_renderer, rect);
}
