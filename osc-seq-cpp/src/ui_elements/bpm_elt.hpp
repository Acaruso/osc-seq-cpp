#pragma once
#include <functional>
#include <string>

#include <SDL.h>

#include "../store/store.hpp"
#include "../store/coord.hpp"

void bpm_elt(
    std::string id,
    Coord& coord,
    int& bpm,
    Store& store,
    std::function<void()> on_click
);
