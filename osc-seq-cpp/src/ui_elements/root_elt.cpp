#include "root_elt.hpp"
#include "grid_elt.hpp"
#include "rect.hpp"

int outer_int = 3;

auto fn = [&] () {
    printf("hello lambda %d\n", outer_int);
    outer_int++;
};

void root_elt(Store& store) {
    do_rect(store.rect, store.ui_state, store.window_renderer);

    do_grid(
        store.grid,
        store.ui_state,
        store.window_renderer,
        fn
    );
}
