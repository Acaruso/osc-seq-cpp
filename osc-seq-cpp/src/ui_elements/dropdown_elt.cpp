#include "dropdown_elt.hpp"

#include "../systems/control_system/dropdown_utils.hpp"
#include "rect_elt.hpp"
#include "text_elt.hpp"

#include <iostream>

void dropdown_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    auto& ee = store.event_editor;
    auto& subfield = field.get_selected_subfield(store.event_editor);
    auto& options_subfield = std::get<Options_Subfield>(subfield);

    auto value_display_res = field.get_display();
    auto& idxs = value_display_res.subfield_idxs[store.event_editor.selected_col];

    Coord dropdown_col_coord{
        coord.x + (idxs.first * store.font_width),
        coord.y + store.font_size
    };

    Dropdown_Entry* cur = &options_subfield.dropdown_list;

    for (int i = 0; i <= store.event_editor.selected_dropdown_col; ++i) {
        dropdown_col_elt(cur, i, field, dropdown_col_coord, store);
        int max_width = get_max_width(cur->subentries);
        int sel_row = ee.selected_dropdown_rows[i];

        dropdown_col_coord.x += 2 + (max_width * store.font_width);
        dropdown_col_coord.y += (sel_row * store.font_size);

        cur = &(cur->subentries[sel_row]);
    }
}

void dropdown_col_elt(
    Dropdown_Entry* dropdown_list,
    int col,
    Event_Field& field,
    Coord& coord,
    Store& store
) {
    int max_width = get_max_width(dropdown_list->subentries);

    dropdown_frame_elt(dropdown_list->subentries, max_width, coord, store);

    for (int i = 0; i < dropdown_list->subentries.size(); ++i) {
        auto& elt = dropdown_list->subentries[i];
        std::string s = elt.key;
        Coord text_coord{
            coord.x,
            coord.y + (i * store.font_size)
        };
        text_elt(s, text_coord, store, 5);

        if (should_show_dropdown_selection(i, col, store.event_editor)) {
            Coord selection_coord{
                coord.x,
                coord.y + (i * store.font_size)
            };
            dropdown_selection_elt(max_width, selection_coord, store);
        }
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
        coord.y,
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

bool should_show_dropdown_selection(
    int row,
    int col,
    Event_Editor& ee
) {
    return (
        ee.selected_dropdown_col == col
        && ee.selected_dropdown_rows[ee.selected_dropdown_col] == row
    );
}

bool should_show_next_col(
    Dropdown_Entry& dropdown_entry,
    Event_Editor& ee
) {
    return (!get_selected_dropdown_entry(dropdown_entry, ee)->subentries.empty());

    // return (
    //     ee.selected_dropdown_row == row
    //     && !dropdown_entry.subentries.empty()
    // );
}
