#pragma once

#include "../store/store.hpp"
#include "../store/coord.hpp"

void dropdown_elt(
    Event_Field& field,
    Coord coord,
    Store& store
);

void dropdown_frame_elt(
    std::vector<std::string>& dropdown_list,
    int max_width,
    std::pair<int, int>& idxs,
    Coord coord,
    Store& store
);

void dropdown_selection_elt(
    int max_width,
    Coord coord,
    Store& store
);

int get_max_width(std::vector<std::string>& dropdown_list);
