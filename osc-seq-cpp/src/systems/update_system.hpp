#pragma once

#include <vector>

#include "../store/grid/grid.hpp"
#include "../store/grid/grid_cell.hpp"
#include "../store/register.hpp"
#include "../store/store.hpp"

struct Dynamic_Event
{
    int time_to_trigger;
    int row;
    Grid_Cell grid_cell;
};

struct Time_Data
{
    int clock;
    int steps_per_seq;
    int frames_per_step;
    int frames_per_seq;
};

void update_system(Store& store);

void update_clock_grid_system(
    Seq_Grid& seq_grid,
    Time_Data& time_data
);

void handle_event_system(
    Seq_Grid& seq_grid,
    std::vector<Register>& registers,
    Grid_Cell& default_cell,
    Time_Data& time_data,
    std::vector<Dynamic_Event>& dyn_events
);

void handle_event(
    Grid_Cell& grid_cell,
    Grid_Cell& default_cell,
    Event_Grid& grid,
    std::vector<Register>& registers,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row_idx,
    Row_Metadata& row_meta
);

bool should_event_trigger(
    Grid_Cell& grid_cell,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
);

bool eval_cond(
    Event_Field* field,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
);

int get_source_val(
    std::string type,
    Int_Subfield field,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
);

void set_meta_mods(
    Grid_Cell& grid_cell,
    Event_Grid& grid,
    std::vector<Register>& registers,
    Row_Metadata& row_meta
);

void add_delay(
    Grid_Cell& grid_cell,
    Grid_Cell& default_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events,
    int row
);

bool should_delay(Grid_Cell& grid_cell);

std::pair<int, int> get_delay(Grid_Cell& grid_cell);

std::vector<Dynamic_Event> get_dynamic_events(
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
);

void add_retriggers(
    Grid_Cell& grid_cell,
    Grid_Cell& default_cell,
    Time_Data& time_data,
    std::vector<Dynamic_Event>& dyn_events,
    int row
);

bool edge_trigger(Time_Data& time_data);

int get_tick(Time_Data& time_data);

struct Get_Ticks_Res
{
	int tick;
	int prev_tick;
};

Get_Ticks_Res get_ticks(Time_Data& time_data);
