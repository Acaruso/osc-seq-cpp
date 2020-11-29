#pragma once

#include <functional>

#include "../../store/coord.hpp"
#include "../../store/grid/grid.hpp"
#include "../../store/image.hpp"
#include "../../store/store.hpp"

void grid_cell_elt(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
);
