#include "sequencer.hpp"
#include "store/ui_state.hpp"
#include "store/grid.hpp"
#include "util.hpp"
#include "ui_elements/grid_elt.hpp"
#include "systems/input_system.hpp"
#include "systems/control_system.hpp"

void testfn() {
    printf("hello testfn\n");
}

int outer_int = 3;

auto fn = [&] () {
    printf("hello lambda %d\n", outer_int);
    outer_int++;
};

void loop(Store& store) {
	while (!store.ui_state.quit) {
		clear_window(store.window_renderer);

        input_system(store.ui_state);

        control_system(store);

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

		// render backbuffer
		SDL_RenderPresent(store.window_renderer);

        // unset click
		store.ui_state.click = false;

        store.clock = (store.clock + 1) % 2048;

		// sleep
		SDL_Delay(10);
	}
}
