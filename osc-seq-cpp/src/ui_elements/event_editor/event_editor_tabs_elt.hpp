#pragma once

#include "../../store/coord.hpp"
#include "../../store/store.hpp"

void event_editor_tabs_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
);

void event_editor_tab_elt(
    std::string tab,
    bool selected,
    Coord& coord,
    Store& store
);

void select_box_elt(
    std::string tab,
    Coord& coord,
    Store& store
);
