#pragma once

#include <functional>

#include <SDL.h>

#include "../store/coord.hpp"
#include "../store/grid/grid.hpp"
#include "../store/grid/seq_grid.hpp"
#include "../store/store.hpp"
#include "../store/ui_state.hpp"

void grid_elt(
    Coord coord,
    int padding,
    Event_Grid& grid,
    Store& store,
    std::function<void()> on_click
);

void grid_elt_clickable(
    Coord coord,
    int padding,
    Event_Grid& grid,
    Seq_Grid& seq_grid,
    Store& store,
    std::function<void()> on_click
);

void grid_select_elt(
    Coord coord,
    int padding,
    Event_Grid& grid,
    Seq_Grid& seq_grid,
    Store& store
);

void pattern_grid_elt(
    Coord coord,
    int padding,
    Pattern_Grid& grid,
    Store& store,
    std::function<void()> on_click
);

Image_Set& get_image_set(int col, std::unordered_map<std::string, Image_Set>& images);
