#pragma once

#include "../store/coord.hpp"
#include "../store/grid.hpp"
#include "../store/grid_cell.hpp"
#include "../store/store.hpp"

void event_editor_wrapper_elt(
    Coord& coord,
    Store& store
);

void event_editor_selector(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
);

void event_editor_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
);

void meta_event_editor_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
);

void event_editor_row_elt(
    Grid_Cell_Data& grid_cell_data,
    bool toggled,
    Coord& coord,
    int index,
    Store& store
);

Coord get_selector_coord(int selected_row, Grid_Cell& grid_cell, int line_height, Coord& coord);
