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

    handle_event_system(store.seq_grid, store.registers, store.default_cell, time_data, dyn_events);

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
    std::vector<Register>& registers,
    Grid_Cell& default_cell,
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
                default_cell,
                grid,
                registers,
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
            default_cell,
            grid,
            registers,
            td,
            dyn_events,
            d_event.row,
            row_meta
        );
    }
}

void handle_event(
    Grid_Cell& grid_cell,
    Grid_Cell& default_cell,
    Event_Grid& grid,
    std::vector<Register>& registers,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row_idx,
    Row_Metadata& row_meta
) {
    if (grid_cell.toggled) {
        if (should_event_trigger(grid_cell, registers, row_meta)) {
            set_meta_mods(grid_cell, grid, registers, row_meta);
            if (should_delay(grid_cell)) {
                add_delay(grid_cell, default_cell, td, dyn_events, row_idx);
            } else {
                send_osc_packet(grid_cell);
                add_retriggers(grid_cell, default_cell, td, dyn_events, row_idx);
            }
        }
        grid_cell.reset_meta_mods();
    }
}

bool should_event_trigger(
    Grid_Cell& grid_cell,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
) {
    bool b1 = eval_cond(
        grid_cell,
        "cond1",
        registers,
        row_meta
    );

    bool b2 = eval_cond(
        grid_cell,
        "cond2",
        registers,
        row_meta
    );

    return b1 && b2;
}

bool eval_cond(
    Grid_Cell& grid_cell,
    std::string key,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
) {
    auto& field = grid_cell.get_event_field(key);

    int s1 = get_source_val(
        field.get_subfield<Options_Subfield>("source1_type").get_selected_option(),
        field.get_subfield<Int_Subfield>("source1_const"),
        registers,
        row_meta
    );

    int s2 = get_source_val(
        field.get_subfield<Options_Subfield>("source2_type").get_selected_option(),
        field.get_subfield<Int_Subfield>("source2_const"),
        registers,
        row_meta
    );

    std::string comp_type = field.get_subfield<Options_Subfield>("comp_type").get_selected_option();

    if (comp_type == "<") {
        return s1 < s2;
    } else if (comp_type == "<=") {
        return s1 <= s2;
    } else if (comp_type == ">") {
        return s1 > s2;
    } else if (comp_type == ">=") {
        return s1 >= s2;
    } else if (comp_type == "==") {
        return s1 == s2;
    }



    switch (comp_type) {
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



    auto& x = grid_cell.get_event_value<Conditional_Field>(key);

    int s1 = get_source_val(x.source1_type, x.source1_const, registers, row_meta);
    int s2 = get_source_val(x.source2_type, x.source2_const, registers, row_meta);

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

int get_source_val(
    std::string type,
    Int_Subfield field,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
) {
    if (type == "Const") {
        return field.data + field.meta_mod;
    } else if (type == "RNG") {
        return row_meta.rng;
    } else if (type == "Reg0") {
        return registers[0].value;
    } else if (type == "Reg1") {
        return registers[1].value;
    }
}

int apply_mod_op(int meta_mod, Mod_Op mod_op, int amnt)
{
    if (mod_op == Plus_Eq) {
        return meta_mod + amnt;
    } else if (mod_op == Minus_Eq) {
        return meta_mod - amnt;
    } else if (mod_op == Assn) {
        return amnt;
    } else {
        return 0;
    }
}

int apply_mod_op(int meta_mod, Mod_Op mod_op, int amnt, int modulus)
{
    if (mod_op == Plus_Eq) {
        return (meta_mod + amnt) % modulus;
    } else if (mod_op == Minus_Eq) {
        if (meta_mod - amnt >= 0) {
            return meta_mod - amnt;
        } else {
            return 0; // only wrap around going upwards
            // return (meta_mod - amnt) + modulus;
        }
    } else if (mod_op == Assn) {
        return amnt % modulus;
    } else {
        return 0;
    }
}

void set_meta_mods(
    Grid_Cell& grid_cell,
    Event_Grid& grid,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
) {
    auto& mod = grid_cell.get_event_value<Mod_Field>("mod");

    int amnt;
    if (mod.source1_type == Const) {
        amnt = mod.source1_const.data;
    } else if (mod.source1_type == RNG) {
        amnt = row_meta.rng;
    } else if (mod.source1_type == Reg0) {
        amnt = registers[0].value;
    } else if (mod.source1_type == Reg1) {
        amnt = registers[1].value;
    }

    auto& tv = grid_cell.get_event_value<Mod_Field>("mod").target;
    auto& t = grid.data[tv.first.data][tv.second.data];

    switch (mod.mod_dest) {
        case Cond1_Const1: {
            auto& x = t.get_event_value<Conditional_Field>("cond1");
            x.source1_const.meta_mod = apply_mod_op(
                x.source1_const.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Cond1_Const2: {
            auto& x = t.get_event_value<Conditional_Field>("cond1");
            x.source2_const.meta_mod = apply_mod_op(
                x.source2_const.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Cond2_Const1: {
            auto& x = t.get_event_value<Conditional_Field>("cond2");
            x.source1_const.meta_mod = apply_mod_op(
                x.source1_const.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Cond2_Const2: {
            auto& x = t.get_event_value<Conditional_Field>("cond2");
            x.source2_const.meta_mod = apply_mod_op(
                x.source2_const.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Retrigger: {
            auto& x = t.get_event_value<Int_Field>("retrigger");
            x.meta_mod = apply_mod_op(
                x.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Note: {
            auto& x = t.get_event_value<Int_Field>("note");
            x.meta_mod = apply_mod_op(
                x.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Duration: {
            auto& x = t.get_event_value<Int_Field>("duration");
            x.meta_mod = apply_mod_op(
                x.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Volume: {
            auto& x = t.get_event_value<Int_Field>("volume");
            x.meta_mod = apply_mod_op(
                x.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Pan: {
            auto& x = t.get_event_value<Int_Field>("pan");
            x.meta_mod = apply_mod_op(
                x.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Aux: {
            auto& x = t.get_event_value<Int_Field>("aux");
            x.meta_mod = apply_mod_op(
                x.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Delay1: {
            auto& x = t.get_event_value<Int_Pair_Field>("delay");
            x.first.meta_mod = apply_mod_op(
                x.first.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Delay2: {
            auto& x = t.get_event_value<Int_Pair_Field>("delay");
            x.second.meta_mod = apply_mod_op(
                x.second.meta_mod,
                mod.mod_op,
                amnt
            );
            break;
        }
        case Mod_Reg0: {
            auto& reg = registers[0];
            reg.value = apply_mod_op(
                reg.value,
                mod.mod_op,
                amnt,
                reg.mod
            );
            break;
        }
        case Mod_Reg1: {
            auto& reg = registers[1];
            reg.value = apply_mod_op(
                reg.value,
                mod.mod_op,
                amnt,
                reg.mod
            );
            break;
        }
    }
}

void add_delay(
    Grid_Cell& grid_cell,
    Grid_Cell& default_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row
) {
    auto delay = get_delay(grid_cell);
    Grid_Cell new_grid_cell{grid_cell};
    new_grid_cell.init_event_field("cond1", default_cell);
    new_grid_cell.init_event_field("cond2", default_cell);
    new_grid_cell.init_event_field("delay", default_cell);
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
    return std::pair<int, int>(
        value.first.data + value.first.meta_mod,
        value.second.data + value.second.meta_mod
    );
}

void add_retriggers(
    Grid_Cell& grid_cell,
    Grid_Cell& default_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row
) {
    auto& field = grid_cell.get_event_value<Int_Field>("retrigger");
    int retrigger = field.data + field.meta_mod;

    Grid_Cell new_grid_cell{grid_cell};
    new_grid_cell.init_event_field("cond1", default_cell);
    new_grid_cell.init_event_field("cond2", default_cell);
    new_grid_cell.init_event_field("retrigger", default_cell);
    new_grid_cell.init_event_field("mod", default_cell);

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
