#include "draw_system.hpp"
#include "../ui_elements/rect.hpp"
#include "../ui_elements/grid_elt.hpp"
#include <SDL.h>

int outer_int = 3;

auto fn = [&] () {
    printf("hello lambda %d\n", outer_int);
    outer_int++;
};

void draw_system(Store& store) {
    do_rect(store.rect, store.ui_state, store.window_renderer);

    do_grid(
        store.grid,
        store.ui_state,
        store.window_renderer,
        fn
        // [&] () {
        //     printf("hello lambda %d\n", outer_int);
        //     outer_int++;
        // }
    );

    SDL_RenderPresent(store.window_renderer);
}
