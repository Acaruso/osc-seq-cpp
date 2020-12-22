#include "sequencer.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "sdl/sdl_wrapper.hpp"
#include "systems/control_system.hpp"
#include "systems/draw_system.hpp"
#include "systems/input_system.hpp"
#include "systems/update_system.hpp"

void loop(Store& store)
{
    while (!store.ui_state.quit) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        clear_window(store.window_renderer);

        input_system(store.ui_state);

        control_system(store);

        update_system(store);

        draw_system(store);

        // unset events
        store.ui_state.keydown_event = false;

        store.prev_ui_state = store.ui_state;

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        Uint32 dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        // std::cout << dur << std::endl;

        Uint32 time_to_sleep = dur > 10 ? 10 : 10 - dur;

        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
    }
}
