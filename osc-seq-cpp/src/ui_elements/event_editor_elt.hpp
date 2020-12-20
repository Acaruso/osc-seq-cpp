#pragma once

#include "../store/coord.hpp"
#include "../store/event_editor.hpp"
#include "../store/grid/grid.hpp"
#include "../store/grid/grid_cell.hpp"
#include "../store/store.hpp"

void event_editor_wrapper_elt(
    Coord& coord,
    Store& store
);

void event_editor_selector_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
);

void event_editor_body_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
);

void event_editor_row_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    Coord& coord,
    int index,
    Store& store
);

bool should_show_underline(
    Event_Field& field,
    int index,
    Event_Editor& ee
);

void underline_elt(
    Value_Display_Res value_display_res,
    Event_Field& field,
    Coord& coord,
    Store& store
);
