#pragma once

#include "../store/color.hpp"
#include "../store/coord.hpp"
#include "../store/register.hpp"
#include "../store/store.hpp"

void registers_elt(Coord& coord, Store& store);

void register_elt(Register& reg, Color& color, Coord& coord, Store& store);
