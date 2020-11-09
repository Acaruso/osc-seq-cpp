#include "root_elt.hpp"
#include "grid_elt.hpp"
#include "seq_grid_elt.hpp"
#include "rect_elt.hpp"
#include "../store/rect.hpp"

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

    /*
    grid_elt_clickable(
        store.grid,
        store.ui_state,
        store.window_renderer,
        []() {}
    );

    grid_elt(
        store.grid2,
        store.ui_state,
        store.window_renderer,
        []() {}
    );
    */
}
