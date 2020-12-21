#include "dropdown_elt.hpp"

#include "rect_elt.hpp"

void dropdown_elt(
    Event_Field& field,
    Coord coord,
    Store& store
) {
    if (store.ui_state.mode == Dropdown) {
        Rect rect{
            0,
            0,
            30,
            30
        };
        Color color{0, 0, 0, 255};
        rect_elt(rect, color, store);
    }
}
