#include "sequencer.hpp"
#include "store/ui_state.hpp"
#include "store/grid.hpp"
#include "util.hpp"
#include "ui_elements/grid_elt.hpp"

void loop(Store& store) {
	while (!store.ui_state.quit) {
		clear_window(store.window_renderer);

		handle_input_events(store.ui_state);

        do_rect(store.rect, store.ui_state, store.window_renderer);
        do_grid(store.grid, store.ui_state, store.window_renderer);

		// render backbuffer
		SDL_RenderPresent(store.window_renderer);

        // unset click
		store.ui_state.click = false;

        store.clock = (store.clock + 1) % 2048;

		// sleep
		SDL_Delay(10);
	}
}
