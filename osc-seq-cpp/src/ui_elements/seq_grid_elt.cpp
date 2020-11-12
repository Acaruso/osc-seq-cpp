#include "seq_grid_elt.hpp"

void seq_grid_elt(
    Coord coord,
    Seq_Grid& seq_grid,
    Store& store,
    std::function<void()> on_click
) {
    int padding = 2;

    Coord clock_grid_coord = { coord.x, coord.y };

    grid_elt(
        clock_grid_coord,
        padding,
        seq_grid.clock_grid,
        store,
        []() {}
    );

    Coord clickable_grid_coord = {
        coord.x,
        coord.y + seq_grid.clock_grid.rect_h + padding
    };

    grid_elt_clickable(
        clickable_grid_coord,
        padding,
        seq_grid.clickable_grid,
        store,
        []() {}
    );
}
