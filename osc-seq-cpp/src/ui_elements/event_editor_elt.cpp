#include "event_editor_elt.hpp"

#include <string>

#include "../store/grid.hpp"
#include "text_elt.hpp"

void event_editor_elt(
    Coord& coord,
    Store& store
) {
    text_elt(
        "event editor",
        coord,
        store
    );

    int row = store.seq_grid.selection_row;
    int col = store.seq_grid.selection_col;

    Grid_Cell grid_cell = store.seq_grid.clickable_grid.data[row][col];

    Coord prob_coord = { coord.x, coord.y + 20 };
    text_elt(
        "probability: " + std::to_string(grid_cell.probability),
        prob_coord,
        store
    );
}
