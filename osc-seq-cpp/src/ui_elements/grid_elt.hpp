#pragma once

#include <functional>

#include <SDL.h>

#include "../store/coord.hpp"
#include "../store/grid.hpp"
#include "../store/store.hpp"
#include "../store/ui_state.hpp"

void grid_elt(
    Coord coord,
    int padding,
    Grid& grid,
    Store& store,
    std::function<void()> on_click
);

void grid_elt_clickable(
    Coord coord,
    int padding,
    Grid& grid,
    int selected_row,
    int selected_col,
    Store& store,
    std::function<void()> on_click
);

void grid_for_each(Grid& grid, std::function<void(Grid_Cell&, int, int)> fn);

Image_Set& get_image_set(int col, std::unordered_map<std::string, Image_Set>& images);
