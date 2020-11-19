#include "event_editor_elt.hpp"

#include <iostream>
#include <string>

#include "image_elt.hpp"
#include "text_elt.hpp"

void event_editor_row_elt(
    std::string key,
    std::string value,
    bool toggled,
    Coord coord,
    int index,
    Store& store
);

void event_editor_wrapper_elt(
    Coord& coord,
    Store& store
) {
    Grid_Cell& grid_cell = store.seq_grid.get_selected();

    Coord select_coord = get_selector_coord(
        store.event_editor.selected_row,
        grid_cell,
        coord
    );

    image_elt(store.images["select-event-editor"], select_coord, store);

    event_editor_elt(grid_cell, coord, store);

    if (grid_cell.has_meta) {
        Coord meta_coord {
            coord.x,
            coord.y + ((grid_cell.data.size() + 1) * 20)
        };
        meta_event_editor_elt(grid_cell, meta_coord, store);
    }
}

void event_editor_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    text_elt("Event Editor", coord, store);

    int i = 0;

    for (auto& row : grid_cell.data) {
        event_editor_row_elt(
            row.key, row.get_value_str(), grid_cell.toggled, coord, i++, store
        );
    }
}

void meta_event_editor_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    text_elt("Meta Event Editor", coord, store);

    int i = 0;

    // event_editor_row_elt(
    //     "num targets",
    //     std::to_string(grid_cell.get_meta_data("targets").targets.size()),
    //     grid_cell.toggled,
    //     coord,
    //     i++,
    //     store
    // );

    for (auto& row : grid_cell.meta_data) {
        event_editor_row_elt(
            row.key, row.get_value_str(), grid_cell.toggled, coord, i++, store
        );
    }
}

void event_editor_row_elt(
    std::string key,
    std::string value,
    bool toggled,
    Coord coord,
    int index,
    Store& store
) {
    if (!toggled) {
        value = "";
    }
    Coord c = { coord.x, (coord.y + 20) + (index * 20) };
    text_elt(key + ": " + value, c, store);
}

Coord get_selector_coord(int selected_row, Grid_Cell& grid_cell, Coord coord)
{
    // data
    if (selected_row < grid_cell.data.size()) {
        return {
            coord.x - 20,
            coord.y + 20 + (20 * selected_row)
        };
    // meta data
    } else {
        return {
            coord.x - 20,
            coord.y + 40 + (20 * selected_row)
        };
    }
}
