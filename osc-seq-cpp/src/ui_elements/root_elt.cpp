#include "root_elt.hpp"
#include "grid_elt.hpp"
#include "rect.hpp"

int outer_int = 3;

auto fn = [&]() {
    // printf("hello lambda %d\n", outer_int);
    // outer_int++;
};

Rect rect2(30, 30, 200, 300);

bool rect2_toggled = true;
auto rect2_on_click = [&]() {
    rect2_toggled = !rect2_toggled;
    printf("%d\n", rect2_toggled);
};

void root_elt(Store& store) {
    do_rect(
        store.rect,
        true,
        store.ui_state,
        store.window_renderer,
        []() {}
    );

    do_rect(
        rect2,
        rect2_toggled,
        store.ui_state,
        store.window_renderer,
        rect2_on_click
    );

    do_grid(
        store.grid,
        store.ui_state,
        store.window_renderer,
        fn
    );
}
