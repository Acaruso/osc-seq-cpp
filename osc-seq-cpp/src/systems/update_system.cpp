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
    int frames_per_step = 24;
    // int frames_per_step = store.time_divisions.n16;
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
    auto& should_trigger = grid_cell.get_event_field("should_trigger")
        .get_subfield<Int_Subfield>("should_trigger_subfield");

    bool b = (should_trigger.data + should_trigger.meta_mod >= 1);

    for (auto field : grid_cell.get_fields_by_flag(Cond_Field)) {
        b = b && eval_cond(field, registers, row_meta);
    }

    return b;
}

bool eval_cond(
    Event_Field* field,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
) {
    int s1 = get_source_val(
        field->get_subfield<Options_Subfield>("source1_type").get_selected_option(),
        field->get_subfield<Int_Subfield>("source1_const"),
        registers,
        row_meta
    );

    int s2 = get_source_val(
        field->get_subfield<Options_Subfield>("source2_type").get_selected_option(),
        field->get_subfield<Int_Subfield>("source2_const"),
        registers,
        row_meta
    );

    std::string comp_type = field->get_subfield<Options_Subfield>("comp_type").get_selected_option();

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
    } else {
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
    } else if (type == "$0") {
        return registers[0].value;
    } else if (type == "$1") {
        return registers[1].value;
    }
}

int apply_mod_op(int meta_mod, std::string mod_op, int amnt)
{
    if (mod_op == "+=") {
        return meta_mod + amnt;
    } else if (mod_op == "-=") {
        return meta_mod - amnt;
    } else if (mod_op == "=") {
        return amnt;
    } else {
        return 0;
    }
}

int apply_mod_op(int meta_mod, std::string mod_op, int amnt, int modulus)
{
    if (mod_op == "+=") {
        return (meta_mod + amnt) % modulus;
    } else if (mod_op == "-=") {
        if (meta_mod - amnt >= 0) {
            return meta_mod - amnt;
        } else {
            return 0; // only wrap around going upwards
            // return (meta_mod - amnt) + modulus;
        }
    } else if (mod_op == "=") {
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
    auto mod_fields = grid_cell.get_fields_by_flag(Mod_Field);

    for (auto& mod : mod_fields) {
        std::string source1_type_option = mod->get_subfield<Options_Subfield>("source1_type")
            .get_selected_option();

        int amnt;
        if (source1_type_option == "Const") {
            amnt = mod->get_subfield<Int_Subfield>("source1_const").data;
        } else if (source1_type_option == "RNG") {
            amnt = row_meta.rng;
        } else if (source1_type_option == "$0") {
            amnt = registers[0].value;
        } else if (source1_type_option == "$1") {
            amnt = registers[1].value;
        }

        auto& target_row = mod->get_subfield<Int_Subfield>("target_row");
        auto& target_col = mod->get_subfield<Int_Subfield>("target_col");

        auto& target_cell = grid.data[target_row.data][target_col.data];

        std::string mod_op = mod->get_subfield<Options_Subfield>("mod_op").get_selected_option();

        auto& mod_subfield = mod->get_subfield<Options_Subfield>("mod_dest");
        auto& dest = target_cell.get_subfield<Int_Subfield>(mod_subfield.subfield_path);

        if (mod_subfield.subfield_path.field_key == "regs") {
            if (mod_subfield.subfield_path.subfield_key == "$0") {
                auto& reg = registers[0];
                reg.value = apply_mod_op(reg.value, mod_op, amnt, reg.mod);
            } else if (mod_subfield.subfield_path.subfield_key == "$1") {
                auto& reg = registers[1];
                reg.value = apply_mod_op(reg.value, mod_op, amnt, reg.mod);
            }
        } else {
            dest.meta_mod = apply_mod_op(dest.meta_mod, mod_op, amnt);
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
    auto& delay_subfield1 = grid_cell.get_subfield<Int_Subfield>("delay", "delay_subfield1");
    auto& delay_subfield2 = grid_cell.get_subfield<Int_Subfield>("delay", "delay_subfield2");

    return std::pair<int, int>(
        delay_subfield1.data + delay_subfield1.meta_mod,
        delay_subfield2.data + delay_subfield2.meta_mod
    );
}

void init_event_field(Event_Field* field, Grid_Cell& default_cell);

void add_retriggers(
    Grid_Cell& grid_cell,
    Grid_Cell& default_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row
) {
    auto& retrigger_field = grid_cell.get_subfield<Int_Subfield>("retrigger", "retrigger_subfield");
    int retrigger = retrigger_field.data + retrigger_field.meta_mod;

    Grid_Cell new_grid_cell{grid_cell};

    new_grid_cell.init_event_field("retrigger", default_cell);

    for (auto& field : new_grid_cell.get_fields_by_flag(Cond_Field)) {
        init_event_field(field, default_cell);
    }

    for (auto& field : new_grid_cell.get_fields_by_flag(Mod_Field)) {
        init_event_field(field, default_cell);
    }

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

void init_event_field(Event_Field* field, Grid_Cell& default_cell)
{
    auto& default_field = default_cell.get_event_field(field->key);
    for (int i = 0; i < field->subfields.size(); ++i) {
        field->subfields[i] = default_field.subfields[i];
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
