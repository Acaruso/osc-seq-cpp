#pragma once

#include <functional>

#include <SDL.h>

#include "../store/color.hpp"
#include "../store/rect.hpp"
#include "../store/store.hpp"

void rect_elt(
    Rect& rect,
    Color& color,
    Store& store
);

void rect_elt_clickable(
    Rect& rect,
    Color& color,
    Store& store,
    std::function<void()> on_click
);
