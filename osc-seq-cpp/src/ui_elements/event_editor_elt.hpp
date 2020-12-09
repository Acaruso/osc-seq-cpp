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

void event_editor_elt(
    std::string header,
    Grid_Cell& grid_cell,
    bool is_meta,
    Coord& coord,
    Store& store
);

void meta_event_editor_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
);

void event_editor_defaults_elt(
    std::string header,
    Grid_Cell& grid_cell,
    bool is_meta,
    Coord& coord,
    Store& store
);

void event_editor_row_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    bool is_meta,
    Coord& coord,
    int index,
    Store& store
);

void event_editor_defaults_row_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    bool is_meta,
    Coord& coord,
    int index,
    Store& store
);

Coord get_selector_coord(
    int selected_row,
    int line_height,
    Grid_Cell& grid_cell,
    Coord& coord
);

bool should_show_underline(
    Event_Field& field,
    Grid_Cell& grid_cell,
    bool is_meta,
    int index,
    Event_Editor& ee
);

void underline_elt(
    std::string text,
    Event_Field& field,
    Coord& coord,
    Store& store
);

Coord get_delay_underline_coord(
    std::string text,
    Coord row_coord,
    int font_width,
    Event_Editor& event_editor
);

Coord get_target_underline_coord(
    std::string text,
    Coord row_coord,
    int font_width,
    Event_Editor& event_editor
);
