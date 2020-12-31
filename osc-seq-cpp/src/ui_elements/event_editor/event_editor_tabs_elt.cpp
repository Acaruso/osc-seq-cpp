#include "event_editor_tabs_elt.hpp"

#include <string>
#include <vector>

#include "../image_elt.hpp"
#include "../text_elt.hpp"

void event_editor_tabs_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    std::string text;
    int num_rows = 2;
    int num_cols = 4;
    int x_coord = coord.x;
    int y_coord = coord.y;

    for (int i = 0; i < num_rows; i++) {
        for (int k = 0; k < num_cols; k++) {
            int idx = (i * num_cols) + k;
            auto& tab = grid_cell.tabs[idx];

            Coord tab_coord = { x_coord, y_coord };

            bool selected = (
                (store.event_editor.selected_tab / num_cols) == i
                && (store.event_editor.selected_tab % num_cols) == k
            );

            text = tab.key;
            text.insert(text.size(), 5 - text.size(), ' ');

            event_editor_tab_elt(text, selected, tab_coord, store);
            x_coord += (text.size() + 1) * store.font_width;
        }
        x_coord = coord.x;
        y_coord += store.font_size;
    }
}

void event_editor_tab_elt(
    std::string tab,
    bool selected,
    Coord& coord,
    Store& store
) {
    text_elt(tab, coord, store);
    if (selected) {
        select_box_elt(tab, coord, store);
    }
}

void select_box_elt(
    std::string tab,
    Coord& coord,
    Store& store
) {
    // lower
    for (int i = 0; i < tab.size(); ++i) {
        Coord underline_coord = {
            coord.x + (i * store.font_width),
            coord.y + 14
        };
        image_elt(store.images["select-underline"], underline_coord, store);
    }

    // upper
    for (int i = 0; i < tab.size(); ++i) {
        Coord underline_coord = {
            coord.x + (i * store.font_width),
            coord.y - 2
        };
        image_elt(store.images["select-underline"], underline_coord, store);
    }

    // left
    Coord v1_coord = {
        coord.x - 2,
        coord.y - 2
    };
    image_elt(store.images["select-vertical-left"], v1_coord, store);

    // right
    Coord v2_coord = {
        coord.x + (tab.size() * store.font_width),
        coord.y - 2
    };
    image_elt(store.images["select-vertical-right"], v2_coord, store);
}
