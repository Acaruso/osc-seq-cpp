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

Rect rect2(30, 30, 200, 300, false);

auto rect2_on_click = [&]() {
    rect2.toggled = !rect2.toggled;
};

void root_elt(Store& store) {
    rect_elt(
        store.rect,
        store.ui_state,
        store.window_renderer,
        []() {}
    );

    rect_elt(
        rect2,
        store.ui_state,
        store.window_renderer,
        rect2_on_click
    );

    seq_grid_elt(
        store.seq_grid,
        store.ui_state,
        store.window_renderer,
        []() {}
    );

    Coord bpm_coord = { 200, 138 };
    bpm_elt(store, bpm_coord, []() {});
}
