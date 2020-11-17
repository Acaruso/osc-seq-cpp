#include "sequencer.hpp"

#include "sdl/sdl_wrapper.hpp"
#include "systems/control_system.hpp"
#include "systems/draw_system.hpp"
#include "systems/input_system.hpp"
#include "systems/update_system.hpp"

void loop(Store& store)
{
	while (!store.ui_state.quit) {
		clear_window(store.window_renderer);

        input_system(store.ui_state);

        control_system(store);

        update_system(store);

        draw_system(store);

        // unset events
        store.ui_state.keydown_event = false;

        store.prev_ui_state = store.ui_state;

		SDL_Delay(10);
	}
}
