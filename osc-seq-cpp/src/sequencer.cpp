#include "sequencer.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "sdl/sdl_wrapper.hpp"
#include "systems/control_system/control_system.hpp"
#include "systems/draw_system.hpp"
#include "systems/input_system.hpp"
#include "systems/update_system.hpp"

Uint64 get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

void loop(Store& store)
{
    Uint64 t_main = get_time();
    Uint64 t_main_interval = 10000;
    Uint64 t_main_next = t_main + t_main_interval;

    Uint64 t_audio = get_time();
    // 60000000 = 1 minute in microseconds
    Uint64 minute = 60000000;
    // compute duration in microseconds of pulse
    Uint64 t_audio_interval = ((minute / store.bpm) / store.PPQ);
    Uint64 t_audio_next = t_audio + t_audio_interval;

    while (!store.ui_state.quit) {
        t_audio = get_time();
        if (t_audio >= t_audio_next) {
            update_system(store);
            t_audio_interval = ((minute / store.bpm) / store.PPQ);
            t_audio_next += t_audio_interval;
        }

        t_main = get_time();
        if (t_main >= t_main_next) {
            t_main_next += t_main_interval;

            clear_window(store.window_renderer);

            input_system(store.ui_state);

            control_system(store);

            draw_system(store);

            store.blink_clock = (store.blink_clock + 1) % 64;

            // unset events
            store.ui_state.keydown_event = false;

            store.prev_ui_state = store.ui_state;
        }
    }
}
