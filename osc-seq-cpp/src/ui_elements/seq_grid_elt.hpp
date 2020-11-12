#pragma once

#include <functional>

#include <SDL.h>

#include "../store/store.hpp"
#include "../store/coord.hpp"
#include "../store/grid.hpp"
#include "../store/ui_state.hpp"
#include "grid_elt.hpp"

void seq_grid_elt(
    Coord coord,
    Seq_Grid& seq_grid,
    Store& store,
    std::function<void()> on_click
);
