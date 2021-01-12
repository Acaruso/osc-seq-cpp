#pragma once

#include "../../store/coord.hpp"
#include "../../store/store.hpp"

void piano_keys_elt(
    Tab& notes_tab,
    Coord& coord,
    Store& store
);

void selected_note_elt(
    int note_num,
    Coord& coord,
    Store& store
);
