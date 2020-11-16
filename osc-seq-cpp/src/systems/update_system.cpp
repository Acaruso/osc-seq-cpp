#include "update_system.hpp"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../osc/osc.hpp"
#include "../store/time_divisions.hpp"

std::vector<Retrigger> retriggers;

void update_system(Store& store) {
    store.time_divisions = get_time_divisions(store.bpm);

    int steps_per_seq = 16;
    int frames_per_step = store.time_divisions.n16;
    int frames_per_seq = frames_per_step * steps_per_seq;

    Time_Data time_data = {
        store.clock,
        steps_per_seq,
        frames_per_step,
        frames_per_seq
    };

    update_clock_grid_system(store.seq_grid.clock_grid, time_data);

    handle_event_system(store.seq_grid.clickable_grid, time_data, retriggers);

    handle_retriggers_system(store.clock, retriggers);

    // update clock at the end
    store.clock = (store.clock + 1) % frames_per_seq;
}

void update_clock_grid_system(Grid& grid, Time_Data& time_data) {
    if (edge_trigger(time_data)) {
        int tick = get_tick(time_data);
        for (auto& grid_elt : grid.data[0]) {
            grid_elt.toggled = false;
        }
        grid.data[0][tick].toggled = true;
    }
}

void handle_event_system(
    Grid& grid,
    Time_Data& time_data,
    std::vector<Retrigger>& retriggers
) {
    if (edge_trigger(time_data)) {
        int tick = get_tick(time_data);
        int channel = 0;
        for (auto& row : grid.data) {
            Grid_Cell& grid_cell = row[tick];
            if (should_event_trigger(grid_cell)) {
                send_osc_packet(channel);
                add_retriggers(grid_cell, channel, time_data, retriggers);
            }
            channel++;
        }
    }
}

void handle_retriggers_system(int clock, std::vector<Retrigger>& retriggers) {
    std::vector<int> to_erase;

    // need to delete from vector backwards
    for (int i = retriggers.size() - 1; i >= 0; --i) {
        Retrigger& retrigger = retriggers[i];
        if (retrigger.time_to_trigger == clock) {
            send_osc_packet(retrigger.channel);
            to_erase.push_back(i);
        }
    }

    for (auto i : to_erase) {
        retriggers.erase(retriggers.begin() + i);
    }
}

void add_retriggers(
    Grid_Cell& grid_cell,
    int channel,
    Time_Data& td,
    std::vector<Retrigger>& retriggers
) {
    if (grid_cell.retrigger > 1) {
        for (int i = 1; i < grid_cell.retrigger; ++i) {
            Retrigger retrigger = {
                td.clock + ((td.frames_per_step / grid_cell.retrigger) * i),
                channel
            };
            retriggers.push_back(retrigger);
        }
    }
}

bool edge_trigger(Time_Data& time_data) {
    Get_Ticks_Res ticks = get_ticks(time_data);
    return (ticks.tick != ticks.prev_tick);
}

bool should_event_trigger(Grid_Cell& grid_cell) {
    if (!grid_cell.toggled) {
        return false;
    } else if (grid_cell.probability == 100) {
        return true;
    } else {
        int random_int = rand() % 100;
        return (random_int < grid_cell.probability);
    }
}

int get_tick(Time_Data& time_data) {
    Get_Ticks_Res ticks = get_ticks(time_data);
    return ticks.tick;
}

int mod_dec(int i, int base);

// get tick and prev tick
Get_Ticks_Res get_ticks(Time_Data& td) {
    int tick = ((td.clock) / td.frames_per_step) % td.steps_per_seq;
    int prev_tick = (mod_dec(td.clock, td.frames_per_seq) / td.frames_per_step) % td.steps_per_seq;
    Get_Ticks_Res res = { tick, prev_tick };
    return res;
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
