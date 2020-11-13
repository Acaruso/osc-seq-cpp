#pragma once

#include <functional>

#include <SDL.h>

#include "../store/coord.hpp"
#include "../store/image_set.hpp"
#include "../store/store.hpp"
#include "../store/ui_state.hpp"

void image_elt(
    Image_Set image_set,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
);

void image_elt_clickable(
    Image_Set image_set,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
);

void image_elt_clickable_toggleable(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
);

void image_elt_toggleable(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    Store& store
);
