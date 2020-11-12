#include <iostream>

#include "../store/coord.hpp"
#include "../store/rect.hpp"
#include "bpm_elt.hpp"
#include "grid_elt.hpp"
#include "image_elt.hpp"
#include "rect_elt.hpp"
#include "root_elt.hpp"

#include "seq_grid_elt.hpp"
#include "text_elt.hpp"

void root_elt(Store& store) {
    rect_elt(
        store.rect,
        store.ui_state,
        store.window_renderer,
        []() {}
    );

    Coord seq_grid_coord = { 30, 30 };
    seq_grid_elt(
        seq_grid_coord,
        store.seq_grid,
        store,
        []() {}
    );

    Coord bpm_coord = { 200, 138 };
    bpm_elt("bpm1", bpm_coord, store.bpm, store, []() {});
}
