#include "dropdown_elt.hpp"

#include "rect_elt.hpp"

void dropdown_elt(
    Event_Field& field,
    Coord coord,
    Store& store
) {
    auto value_display_res = field.get_value_display();
    auto& idxs = value_display_res.subfield_idxs[store.event_editor.selected_col];

    Rect rect{
        coord.x + (idxs.first * store.font_width),
        coord.y + 16,
        30,
        30
    };
    Color color{0, 0, 0, 255};
    rect_elt(rect, color, store);
}
