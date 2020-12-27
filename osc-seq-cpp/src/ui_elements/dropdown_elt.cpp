#include "dropdown_elt.hpp"

#include "rect_elt.hpp"
#include "text_elt.hpp"

#include <iostream>

void dropdown_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    auto& subfield = field.get_selected_subfield(store.event_editor);
    auto& options_subfield = std::get<Options_Subfield>(subfield);

    auto dropdown_list = grid_cell.get_dropdown_list(options_subfield);

    auto value_display_res = field.get_display();
    auto& idxs = value_display_res.subfield_idxs[store.event_editor.selected_col];

    Coord dd_coord{
        coord.x + (idxs.first * store.font_width),
        coord.y + store.font_size
    };

    dropdown_level_elt(dropdown_list, field, dd_coord, store);
}

void dropdown_level_elt(
    std::vector<Dropdown_Entry> dropdown_list,
    Event_Field& field,
    Coord& coord,
    Store& store
) {
    int max_width = get_max_width(dropdown_list);

    dropdown_frame_elt(dropdown_list, max_width, coord, store);

    dropdown_selection_elt(max_width, coord, store);

    for (int i = 0; i < dropdown_list.size(); ++i) {
        auto& elt = dropdown_list[i];
        std::string s = elt.key;
        Coord text_coord = {
            coord.x,
            coord.y + (i * store.font_size)
        };
        text_elt(s, text_coord, store, 5);
        // if (
        //     store.event_editor.selected_dropdown_row == i
        //     && !elt.subentries.empty()
        // ) {
        //     dropdown_level_elt(elt.subentries, field, coord, store);
        // }
    }
}

void dropdown_frame_elt(
    std::vector<Dropdown_Entry>& dropdown_list,
    int max_width,
    Coord& coord,
    Store& store
) {
    Rect background_rect{
        coord.x,
        coord.y,
        max_width * store.font_width,
        dropdown_list.size() * store.font_size
    };
    Color white{255, 255, 255, 0};
    rect_elt(background_rect, white, store, 3);

    Rect outline_rect{
        background_rect.x - 2,
        background_rect.y - 2,
        background_rect.w + 4,
        background_rect.h + 4
    };
    Color blue{51, 153, 255, 0};
    rect_elt(outline_rect, blue, store, 2);
}

void dropdown_selection_elt(
    int max_width,
    Coord& coord,
    Store& store
) {
    Rect select_rect{
        coord.x,
        coord.y + (store.event_editor.selected_dropdown_row * store.font_size),
        max_width * store.font_width,
        store.font_size
    };

    Color color{0, 204, 255, 0};
    rect_elt(select_rect, color, store, 4);
}

int get_max_width(std::vector<Dropdown_Entry>& dropdown_list)
{
    int max_width = 0;
    for (auto& elt : dropdown_list) {
        std::string s = elt.key;
        if (s.size() > max_width) {
            max_width = s.size();
        }
    }
    return max_width;
}
