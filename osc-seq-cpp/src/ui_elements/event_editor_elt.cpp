#include "event_editor_elt.hpp"

#include <string>

#include "../store/grid.hpp"
#include "text_elt.hpp"

void event_editor_elt(
    Coord& coord,
    Store& store
) {
    Grid_Cell grid_cell = store.seq_grid.get_selected();

    text_elt(
        "event editor",
        coord,
        store
    );

    Coord prob_coord = { coord.x, coord.y + 20 };

    std::string prob_str = "probability: " + (grid_cell.toggled
        ? std::to_string(grid_cell.probability)
        : "");

    text_elt(
        prob_str,
        prob_coord,
        store
    );
}
