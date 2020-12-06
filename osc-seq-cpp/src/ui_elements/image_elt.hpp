#pragma once

#include <functional>

#include "../store/coord.hpp"
#include "../store/image.hpp"
#include "../store/store.hpp"

void image_elt(
    Image_Set& image_set,
    Coord& coord,
    Store& store
);

void image_elt_clickable(
    Image_Set& image_set,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
);

void image_elt_clickable_toggleable(
    Image_Set& image_set,
    bool toggled,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
);

void image_elt_toggleable(
    Image_Set& image_set,
    bool toggled,
    Coord& coord,
    Store& store
);

void image_elt_blink(
    Image_Set& image_set,
    Coord& coord,
    Store& store
);
