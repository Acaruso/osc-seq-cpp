#pragma once

#include "../store/coord.hpp"
#include "../store/grid.hpp"
#include "../store/store.hpp"

void event_editor_wrapper_elt(
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
