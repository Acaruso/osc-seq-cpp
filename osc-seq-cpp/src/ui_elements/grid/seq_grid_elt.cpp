#include "seq_grid_elt.hpp"

void seq_grid_elt(
    Coord coord,
    Seq_Grid& seq_grid,
    Store& store,
    std::function<void()> on_click
) {
    int padding = 2;

    // clock grid
    Coord clock_grid_coord = { coord.x, coord.y };

    grid_elt(
        clock_grid_coord,
        padding,
        seq_grid.clock_grid,
        store,
        []() {}
    );

    // event grid
    Coord clickable_grid_coord
    {
        coord.x,
        coord.y + seq_grid.clock_grid.rect_h + (padding * 2)
    };

    grid_elt_clickable(
        clickable_grid_coord,
        padding,
        seq_grid.get_selected_pattern(),
        seq_grid,
        store,
        []() {}
    );
}
