#include "text_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"

void text_elt(std::string text, Coord& coord, Store& store)
{
    draw_text(text, coord, store);
}

void text_elt_draggable(
    std::string id,
    std::string text,
    Coord& coord,
    Store& store,
    std::function<void()> on_click,
    std::function<void(int drag_amount)> on_drag
) {
    FC_Rect fc_rect = draw_text(text, coord, store);

    Rect rect = { fc_rect.x, fc_rect.y, fc_rect.w, fc_rect.h };

    if (is_mousedown_event_inside_rect(rect, store.ui_state, store.prev_ui_state)) {
        store.ui_state.cur_elt_id = id;
    }

    if (store.ui_state.click && store.ui_state.cur_elt_id == id) {
        on_drag(store.ui_state.prev_drag_y - store.ui_state.drag_y);
    }
}
