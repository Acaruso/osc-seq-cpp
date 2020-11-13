#pragma once

#include <functional>

#include <SDL.h>

#include "../store/rect.hpp"
#include "../store/store.hpp"

void rect_elt(
    Rect& rect,
    Store& store,
    std::function<void()> on_click
);
