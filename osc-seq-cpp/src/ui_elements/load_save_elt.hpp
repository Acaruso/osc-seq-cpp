#pragma once

#include <functional>

#include "../store/coord.hpp"
#include "../store/image.hpp"
#include "../store/store.hpp"

void button_load_save_elt(
    std::string text,
    Image_Set& image_set,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
);
