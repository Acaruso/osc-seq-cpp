#include "event_editor_tabs_elt.hpp"

#include <string>
#include <vector>

#include "image_elt.hpp"
#include "text_elt.hpp"

void event_editor_tabs_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    int x_idx = coord.x;

    for (int i = 0; i < grid_cell.tabs.size(); ++i) {
        auto& tab = grid_cell.tabs[i];
        Coord c = { x_idx, coord.y };
        bool selected = (store.event_editor.selected_tab == i);
        event_editor_tab_elt(tab.key, selected, c, store);
        x_idx += (tab.key.size() + 1) * store.font_width;
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
