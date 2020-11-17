#include "event_editor_elt.hpp"

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
    // selector
    Coord select_coord
    {
        coord.x - 20,
        coord.y + 20 + (20 * store.event_editor.cur_selected_field)
    };

    image_elt(store.images["select-event-editor"], select_coord, store);

    Grid_Cell& grid_cell = store.seq_grid.get_selected();

    event_editor_elt(grid_cell, coord, store);

    if (grid_cell.has_meta) {
        Coord meta_coord = { coord.x, coord.y + ((grid_cell.data.size() + 3) * 20) };
        meta_event_editor_elt(grid_cell, meta_coord, store);
    }
}

void event_editor_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    text_elt("Event Editor", coord, store);

    // Grid_Cell& grid_cell = store.seq_grid.get_selected();

    int i = 0;

    std::string prob_val = std::to_string(grid_cell.probability) + "%";

    event_editor_row_elt("probability", prob_val, grid_cell.toggled, coord, i++, store);

    std::string retrigger_val = grid_cell.retrigger == 1
        ? "OFF"
        : std::to_string(grid_cell.retrigger) + "x";

    event_editor_row_elt(
        "retrigger", retrigger_val, grid_cell.toggled, coord, i++, store
    );

    for (auto& row : grid_cell.data) {
        event_editor_row_elt(
            row.key, std::to_string(row.value), grid_cell.toggled, coord, i++, store
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

    std::string target_val = "";

    if (grid_cell.meta_target.row != -1 && grid_cell.meta_target.col != -1) {
        target_val += "[" + std::to_string(grid_cell.meta_target.row);
        target_val += ", " + std::to_string(grid_cell.meta_target.col) + "]";
    }

    event_editor_row_elt(
        "target", target_val, grid_cell.toggled, coord, i++, store
    );
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
