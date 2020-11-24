#pragma once

#include "../store/coord.hpp"
#include "../store/event_editor.hpp"
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
    Event_Field& field,
    bool toggled,
    Coord& coord,
    int index,
    Store& store
);

Coord get_selector_coord(
    int selected_row,
    Grid_Cell& grid_cell,
    int line_height,
    Coord& coord
);

Coord get_delay_underline_coord(
    std::string text,
    Coord row_coord,
    int font_width,
    Event_Editor& event_editor
);
