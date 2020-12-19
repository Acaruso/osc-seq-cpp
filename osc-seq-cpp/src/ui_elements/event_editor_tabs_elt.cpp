#include "event_editor_tabs_elt.hpp"

#include <string>
#include <vector>

#include "image_elt.hpp"
#include "text_elt.hpp"

std::vector<std::string> tabs{"tab1", "tab2", "tab3"};

void event_editor_tabs_elt(
    Coord& coord,
    Store& store
) {
    int x_idx = coord.x;

    for (int i = 0; i < tabs.size(); ++i) {
        Coord c = { x_idx, coord.y };
        event_editor_tab_elt(tabs[i], (i == 1), c, store);
        x_idx += (tabs[i].size() + 1) * store.font_width;
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
