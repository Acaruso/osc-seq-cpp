#include "sequencer.hpp"
#include "systems/input_system.hpp"
#include "systems/control_system.hpp"
#include "systems/update_system.hpp"
#include "systems/draw_system.hpp"

void loop(Store& store) {
	while (!store.ui_state.quit) {
		clear_window(store.window_renderer);

        input_system(store.ui_state);

        control_system(store);

        update_system(store);

        draw_system(store);

        // unset click
		store.ui_state.click = false;

		SDL_Delay(10);
	}
}
