#include "seq_grid_elt.hpp"

void seq_grid_elt(
    Coord coord,
    Seq_Grid& seq_grid,
    Store& store,
    std::function<void()> on_click
) {
    grid_elt(
        coord,
        seq_grid.clock_grid,
        store,
        []() {}
    );

    Coord clickable_coord = { coord.x, coord.y + seq_grid.clock_grid.rect_h };

    grid_elt_clickable(
        clickable_coord,
        seq_grid.clickable_grid,
        store,
        []() {}
    );
}
