#pragma once

#include <functional>
#include <string>

#include <SDL.h>

#include "../store/store.hpp"
#include "../store/coord.hpp"

void arrow_up_down_elt(
    std::string id,
    std::string text,
    Coord& coord,
    int& bpm,
    Store& store,
    std::function<void()> on_up_click,
    std::function<void()> on_down_click,
    std::function<void(int)> on_drag
);
