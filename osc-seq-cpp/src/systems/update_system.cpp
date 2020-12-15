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
    store.blink_clock = (store.blink_clock + 1) % 64;

    if (store.transport_mode == Pause) {
        return;
    }

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

    handle_event_system(store.seq_grid, time_data, dyn_events);

    // update clock
    store.clock = (store.clock + 1) % frames_per_seq;
}

void update_clock_grid_system(Event_Grid& grid, Time_Data& time_data)
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
    Seq_Grid& seq_grid,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
) {
    auto& grid = seq_grid.get_selected_pattern();
    if (edge_trigger(td)) {
        int tick = get_tick(td);
        for (int row_idx = 0; row_idx < grid.data.size(); ++row_idx) {
            auto& row_meta = seq_grid.get_row_metadata(row_idx);
            row_meta.rng = rand() % 100;
            if (row_meta.mute){
                continue;
            }
            auto& row = grid.data[row_idx];
            Grid_Cell& grid_cell = row[tick];
            handle_event(
                grid_cell,
                grid,
                td,
                dyn_events,
                row_idx,
                row_meta
            );
        }
    }

    auto d_events = get_dynamic_events(td, dyn_events);
    for (auto& d_event : d_events) {
        auto& row_meta = seq_grid.get_row_metadata(d_event.row);
        if (row_meta.mute){
            continue;
        }
        handle_event(
            d_event.grid_cell,
            grid,
            td,
            dyn_events,
            d_event.row,
            row_meta
        );
    }
}

void handle_event(
    Grid_Cell& grid_cell,
    Event_Grid& grid,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row_idx,
    Row_Metadata& row_meta
) {
    if (grid_cell.toggled) {
        if (should_event_trigger(grid_cell, row_meta)) {
            set_meta_mods(grid_cell, grid);
            if (should_delay(grid_cell)) {
                add_delay(grid_cell, td, dyn_events, row_idx);
            } else {
                send_osc_packet(grid_cell);
                add_retriggers(grid_cell, td, dyn_events, row_idx);
            }
        }
        reset_meta_mods(grid_cell);
    }
}

bool should_event_trigger(Grid_Cell& grid_cell, Row_Metadata& row_meta)
{
    auto& x = grid_cell.get_event_value<Conditional_Field>("cond");

    int s1, s2;

    if (x.source1_type == Const) {
        s1 = x.source1_const.data;
    } else {
        s1 = row_meta.rng;
    }

    if (x.source2_type == Const) {
        s2 = x.source2_const.data;
    } else {
        s2 = row_meta.rng;
    }

    switch (x.comp_type) {
        case LT:
            return s1 < s2;
        case LT_Eq:
            return s1 <= s2;
        case GT:
            return s1 > s2;
        case GT_Eq:
            return s1 >= s2;
        case Eq:
            return s1 == s2;
        default:
            return false;
    }
}

void set_meta_mods(Grid_Cell& grid_cell, Event_Grid& grid)
{
    auto& pm_value = grid_cell.get_event_value<Int_Field>("probability mod");
    auto& t_value = grid_cell.get_event_value<Int_Pair_Field>("target");
    auto& target = grid.data[t_value.first.data][t_value.second.data];
    auto& target_prob_value = target.get_event_value<Int_Field>("probability");
    target_prob_value.meta_mod += pm_value.data;
}

void reset_meta_mods(Grid_Cell& grid_cell)
{
    auto& prob = grid_cell.get_event_value<Int_Field>("probability");
    prob.meta_mod = 0;
}

void add_delay(
    Grid_Cell& grid_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row
) {
    auto delay = get_delay(grid_cell);
    Grid_Cell new_grid_cell{grid_cell};
    new_grid_cell.init_event_field("probability");
    new_grid_cell.init_event_field("cond");
    new_grid_cell.init_event_field("delay");
    dyn_events.push_back({
        td.clock + ((td.frames_per_step / delay.second) * delay.first),
        row,
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
    auto& value = grid_cell.get_event_value<Int_Pair_Field>("delay");
    return std::pair<int, int>(value.first.data, value.second.data);
}

void add_retriggers(
    Grid_Cell& grid_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row
) {
    int retrigger = grid_cell.get_event_value<Int_Field>("retrigger").data;

    Grid_Cell new_grid_cell{grid_cell};
    new_grid_cell.init_event_field("probability");
    new_grid_cell.init_event_field("cond");
    new_grid_cell.init_event_field("retrigger");
    new_grid_cell.init_event_field("target");
    new_grid_cell.init_event_field("probability mod");

    if (retrigger > 1) {
        int prev = (td.clock / td.frames_per_step) * td.frames_per_step;
        int new_fps = td.frames_per_step - (td.clock - prev);
        for (int i = 1; i < retrigger; ++i) {
            dyn_events.push_back({
                td.clock + ((new_fps / retrigger) * i),
                row,
                new_grid_cell
            });
        }
    }
}

std::vector<Dynamic_Event> get_dynamic_events(
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
) {
    std::vector<Dynamic_Event> v;
    std::vector<int> to_erase;

    for (int i = dyn_events.size() - 1; i >= 0; --i) {
        Dynamic_Event& dyn_event = dyn_events[i];
        if (dyn_event.time_to_trigger == td.clock) {
            v.push_back(dyn_events[i]);
            to_erase.push_back(i);
        }
    }
    for (auto i : to_erase) {
        dyn_events.erase(dyn_events.begin() + i);
    }
    return v;
}

bool edge_trigger(Time_Data& time_data)
{
    Get_Ticks_Res ticks = get_ticks(time_data);
    return (ticks.tick != ticks.prev_tick);
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
