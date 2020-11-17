#include "event_editor_elt.hpp"

#include <string>

#include "../store/grid.hpp"
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

void event_editor_elt(
    Coord& coord,
    Store& store
) {
    // header
    Grid_Cell grid_cell = store.seq_grid.get_selected();

    text_elt(
        "event editor",
        coord,
        store
    );

    // selector
    Coord select_coord
    {
        coord.x - 20,
        coord.y + 20 + (20 * store.event_editor.cur_selected_field)
    };

    image_elt(
        store.images["select-event-editor"],
        select_coord,
        store
    );

    // rows
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
