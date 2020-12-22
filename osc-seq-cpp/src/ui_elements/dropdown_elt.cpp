#include "dropdown_elt.hpp"

#include "rect_elt.hpp"
#include "text_elt.hpp"

#include <iostream>

void dropdown_elt(
    Event_Field& field,
    Coord coord,
    Store& store
) {
    auto value_display_res = field.get_value_display();
    auto dropdown_list = field.get_dropdown_list(store.event_editor);

    int max_width = 0;
    for (auto& s : dropdown_list) {
        if (s.size() > max_width) {
            max_width = s.size();
        }
    }

    auto& idxs = value_display_res.subfield_idxs[store.event_editor.selected_col];
    Rect rect{
        coord.x + (idxs.first * store.font_width),
        coord.y + store.font_size,
        max_width * store.font_width,
        dropdown_list.size() * store.font_size
    };
    Color color{255, 255, 255, 0};
    rect_elt(rect, color, store, 3);

    Rect rect2{
        rect.x - 2,
        rect.y - 2,
        rect.w + 4,
        rect.h + 4
    };
    Color color2{51, 153, 255, 0};
    rect_elt(rect2, color2, store, 2);

    for (int i = 0; i < dropdown_list.size(); ++i) {
        std::string s = dropdown_list[i];
        Coord text_coord = {
            rect.x,
            rect.y + (i * store.font_size)
        };
        text_elt(s, text_coord, store, 4);
    }
}
