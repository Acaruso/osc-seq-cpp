#include "sequencer.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "sdl/sdl_wrapper.hpp"
#include "systems/control_system/control_system.hpp"
#include "systems/draw_system.hpp"
#include "systems/input_system.hpp"
#include "systems/update_system.hpp"

std::chrono::steady_clock::time_point prev_begin = std::chrono::steady_clock::now();

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
    // compute duration in microseconds of pulse (96 PPQ)
    Uint64 t_audio_interval = ((60000000 / store.bpm) / 96);
    store.pulse_length = t_audio_interval;
    Uint64 t_audio_next = t_audio + t_audio_interval;

    while (!store.ui_state.quit) {
        t_audio = get_time();
        if (t_audio > t_audio_next) {
            t_audio_next += t_audio_interval;
            update_system(store);
        }

        t_main = get_time();
        if (t_main >= t_main_next) {
            t_main_next += t_main_interval;

            clear_window(store.window_renderer);

            input_system(store.ui_state);

            control_system(store);

            // update_system(store);

            draw_system(store);

            // unset events
            store.ui_state.keydown_event = false;

            store.prev_ui_state = store.ui_state;
        }
    }
}

/*
void loop(Store& store)
{
    while (!store.ui_state.quit) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        Uint64 ms = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        std::cout << "----------------------" << std::endl;

        std::cout << ms << std::endl;

        clear_window(store.window_renderer);

        input_system(store.ui_state);

        control_system(store);

        update_system(store);

        draw_system(store);

        // unset events
        store.ui_state.keydown_event = false;

        store.prev_ui_state = store.ui_state;

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        Uint32 dur = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

        // std::cout << dur << std::endl;

        Uint32 a = std::chrono::duration_cast<std::chrono::microseconds>(
            begin - prev_begin
        ).count();

        // Uint32 a = std::chrono::duration_cast<std::chrono::microseconds>(
        //     begin - prev_begin
        // ).count() - 10 * 1000;

        std::cout << "a: " << a << std::endl;

        prev_begin = begin;

        Uint32 time_to_sleep = dur > 10 * 1000 ? 10 * 1000 : 10 * 1000 - dur;

        // std::cout << "dur: " << dur << std::endl;

        // std::cout << "time_to_sleep: " << time_to_sleep << std::endl;

        std::this_thread::sleep_for(std::chrono::microseconds(time_to_sleep));
    }
}
*/
