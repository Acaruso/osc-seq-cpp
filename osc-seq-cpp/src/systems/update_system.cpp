#include "update_system.hpp"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../osc/osc.hpp"
#include "../store/time_divisions.hpp"
#include "../util.hpp"

std::vector<Dynamic_Event> dyn_events;

void update_system(Store& store)
{
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

    handle_event_system(store.seq_grid.clickable_grid, time_data, dyn_events);

    handle_dynamic_events_system(time_data, dyn_events);

    // update clock at the end
    store.clock = (store.clock + 1) % frames_per_seq;
}

void update_clock_grid_system(Grid& grid, Time_Data& time_data)
{
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
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
) {
    if (edge_trigger(td)) {
        int tick = get_tick(td);
        for (auto& row : grid.data) {
            Grid_Cell& grid_cell = row[tick];
            handle_event_and_meta(grid_cell, grid, td, dyn_events);
        }
    }
}

void handle_event_and_meta(
    Grid_Cell& grid_cell,
    Grid& grid,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
) {
    if (grid_cell.toggled) {
        if (should_event_trigger(grid_cell)) {
            set_meta_mods(grid_cell, grid);
            if (should_delay(grid_cell)) {
                add_delay(grid_cell, td, dyn_events);
            } else {
                send_osc_packet(grid_cell);
                add_retriggers(grid_cell, td, dyn_events);
            }
        }
        reset_meta_mods(grid_cell);
    }
}

void handle_event(
    Grid_Cell& grid_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
) {
    if (grid_cell.toggled) {
        if (should_event_trigger(grid_cell)) {
            if (should_delay(grid_cell)) {
                add_delay(grid_cell, td, dyn_events);
            } else {
                send_osc_packet(grid_cell);
                add_retriggers(grid_cell, td, dyn_events);
            }
        }
    }
}

void set_meta_mods(Grid_Cell& grid_cell, Grid& grid)
{
    auto& pm_field = grid_cell.get_event_field("probability mod");
    auto& pm_value = std::get<Int_Field>(pm_field.value);

    auto& t_field = grid_cell.get_event_field("target");
    auto& t_value = std::get<Int_Pair_Field>(t_field.value);

    auto& target = grid.data[t_value.first.data][t_value.second.data];

    auto& target_prob = target.get_event_field("probability");
    auto& target_prob_value = std::get<Int_Field>(target_prob.value);

    target_prob_value.meta_mod += pm_value.data;

    std::cout << target_prob_value.meta_mod << std::endl;
}

void reset_meta_mods(Grid_Cell& grid_cell)
{
    auto& field = grid_cell.get_event_field("probability");
    auto& x = std::get<Int_Field>(field.value);
    x.meta_mod = 0;
}

void add_delay(
    Grid_Cell& grid_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
) {
    auto delay = get_delay(grid_cell);
    Grid_Cell new_grid_cell{grid_cell};
    new_grid_cell.init_event_field("delay");
    new_grid_cell.init_event_field("probability");
    dyn_events.push_back({
        td.clock + ((td.frames_per_step / delay.second) * delay.first),
        new_grid_cell
    });
}

bool should_delay(Grid_Cell& grid_cell)
{
    auto delay = get_delay(grid_cell);
    return (delay.first != 0);
}

std::pair<int, int> get_delay(Grid_Cell& grid_cell)
{
    auto& field = grid_cell.get_event_field("delay");
    Int_Pair_Field& value = std::get<Int_Pair_Field>(field.value);
    return std::pair<int, int>(value.first.data, value.second.data);
}

void add_retriggers(
    Grid_Cell& grid_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
) {
    auto& field = grid_cell.get_event_field("retrigger");
    int retrigger = std::get<Int_Field>(field.value).data;

    Grid_Cell new_grid_cell{grid_cell};
    new_grid_cell.init_event_field("retrigger");
    new_grid_cell.init_event_field("probability");
    new_grid_cell.init_event_field("target");
    new_grid_cell.init_event_field("probability mod");

    if (retrigger > 1) {
        int prev = (td.clock / td.frames_per_step) * td.frames_per_step;
        int new_fps = td.frames_per_step - (td.clock - prev);
        for (int i = 1; i < retrigger; ++i) {
            dyn_events.push_back({
                td.clock + ((new_fps / retrigger) * i),
                //td.clock + ((td.frames_per_step / retrigger) * i),
                new_grid_cell
            });
        }
    }
}

void handle_dynamic_events_system(
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
) {
    std::vector<int> to_erase;

    // need to delete from vector backwards
    for (int i = dyn_events.size() - 1; i >= 0; --i) {
        Dynamic_Event& dyn_event = dyn_events[i];
        if (dyn_event.time_to_trigger == td.clock) {
            handle_event(dyn_event.grid_cell, td, dyn_events);
            to_erase.push_back(i);
        }
    }

    for (auto i : to_erase) {
        dyn_events.erase(dyn_events.begin() + i);
    }
}

bool edge_trigger(Time_Data& time_data)
{
    Get_Ticks_Res ticks = get_ticks(time_data);
    return (ticks.tick != ticks.prev_tick);
}

bool should_event_trigger(Grid_Cell& grid_cell)
{
    auto& field = grid_cell.get_event_field("probability");
    auto& x = std::get<Int_Field>(field.value);
    int prob_mod = clamp(x.data + x.meta_mod, x.min, x.max);

    if (prob_mod >= 100) {
        return true;
    } else {
        int random_int = rand() % 100;
        return (random_int < prob_mod);
    }
}

int get_tick(Time_Data& time_data)
{
    Get_Ticks_Res ticks = get_ticks(time_data);
    return ticks.tick;
}

int mod_dec(int i, int base);

// get tick and prev tick
Get_Ticks_Res get_ticks(Time_Data& td)
{
    int tick = ((td.clock) / td.frames_per_step) % td.steps_per_seq;
    int prev_tick = (mod_dec(td.clock, td.frames_per_seq) / td.frames_per_step) % td.steps_per_seq;
    Get_Ticks_Res res = { tick, prev_tick };
    return res;
}

int mod_dec(int i, int base)
{
    int res = i - 1;
    if (res >= 0) {
        return res;
    }
    else {
        return base - 1;
    }
}
