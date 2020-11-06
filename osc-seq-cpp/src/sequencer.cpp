#include "sequencer.hpp"
#include "store/ui_state.hpp"
#include "store/grid.hpp"
#include "util.hpp"
#include "ui_elements/grid_elt.hpp"
#include "systems/input_system.hpp"
#include "systems/control_system.hpp"
#include "systems/draw_system.hpp"

void loop(Store& store) {
	while (!store.ui_state.quit) {
		clear_window(store.window_renderer);

        input_system(store.ui_state);

        control_system(store);

        draw_system(store);

        // unset click
		store.ui_state.click = false;

        store.clock = (store.clock + 1) % 2048;

		// sleep
		SDL_Delay(10);
	}
}
