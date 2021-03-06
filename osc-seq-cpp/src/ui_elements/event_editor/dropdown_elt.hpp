#pragma once

#include "../../store/store.hpp"
#include "../../store/coord.hpp"

void dropdown_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
);

void dropdown_col_elt(
    Dropdown_Entry* dropdown_list,
    int col,
    Event_Field& field,
    Coord& coord,
    Store& store
);

void dropdown_frame_elt(
    std::vector<Dropdown_Entry>& dropdown_list,
    int max_width,
    Coord& coord,
    Store& store
);

void dropdown_selection_elt(
    int max_width,
    Coord& coord,
    Store& store
);

int get_max_width(std::vector<Dropdown_Entry>& dropdown_list);

bool should_show_dropdown_selection(
    int row,
    int col,
    Event_Editor& ee
);

bool should_show_next_col(
    Dropdown_Entry& dropdown_entry,
    Event_Editor& ee
);
