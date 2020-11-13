#include "update_system.hpp"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../osc/osc.hpp"
#include "../store/time_divisions.hpp"

void update_system(Store& store) {
    store.time_divisions = get_time_divisions(store.bpm);

    int step_len = store.time_divisions.n16;
    int max_seq_len = step_len * 16;

    update_clock_grid_system(store.seq_grid.clock_grid, store.clock, step_len, max_seq_len);

    send_osc_system(store.seq_grid.clickable_grid, store.clock, step_len, max_seq_len);

    // update clock at the end
    store.clock = (store.clock + 1) % max_seq_len;
}

void update_clock_grid_system(Grid& grid, int clock, int step_len, int max_seq_len) {
    Get_Ticks_Res ticks = get_ticks(clock, step_len, grid.numCols, max_seq_len);

    if (ticks.tick != ticks.prev_tick) {
        for (auto& grid_elt : grid.data[0]) {
            grid_elt.toggled = false;
        }
        grid.data[0][ticks.tick].toggled = true;
    }
}

int mod_dec(int i, int base) {
    int res = i - 1;
    if (res >= 0) {
        return res;
    }
    else {
        return base - 1;
    }
}

Get_Ticks_Res get_ticks(int clock, int step_len, int seq_len, int max_seq_len) {
    int tick = ((clock) / step_len) % seq_len;
    int prev_tick = (mod_dec(clock, max_seq_len) / step_len) % seq_len;
    Get_Ticks_Res res = { tick, prev_tick };
    return res;
}

void send_osc_system(Grid& grid, int clock, int step_len, int max_seq_len) {
    Get_Ticks_Res ticks = get_ticks(clock, step_len, grid.numCols, max_seq_len);

    if (ticks.tick != ticks.prev_tick) {
        int channel = 0;
        for (auto& row : grid.data) {
            handle_event(row[ticks.tick], channel);
            channel++;
        }
    }
}

void handle_event(Grid_Cell& grid_cell, int channel) {
    if (grid_cell.toggled) {
        if (grid_cell.probability == 100) {
            send_osc_packet(channel);
        } else {
            int random_int = rand() % 100;
            if (random_int < grid_cell.probability) {
                send_osc_packet(channel);
            }
        }
    }
}
