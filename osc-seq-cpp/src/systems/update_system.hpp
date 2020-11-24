#pragma once

#include <vector>

#include "../store/store.hpp"
#include "../store/grid_cell.hpp"

struct Time_Data
{
    int clock;
    int steps_per_seq;
    int frames_per_step;
    int frames_per_seq;
};

struct Dynamic_Event
{
    int time_to_trigger;
    Grid_Cell grid_cell;
};

void update_system(Store& store);

void update_clock_grid_system(Grid& grid, Time_Data& time_data);

void handle_event_system(
    Grid& grid,
    Time_Data& time_data,
    std::vector<Dynamic_Event>& dyn_events
);

void handle_event(
    Grid_Cell& grid_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
);

void add_delay(
    Grid_Cell& grid_cell,
    Time_Data& td,
    std::vector<Dynamic_Event>& dyn_events
);

bool should_delay(Grid_Cell& grid_cell);

std::pair<int, int> get_delay(Grid_Cell& grid_cell);

void handle_dynamic_events_system(Time_Data& td, std::vector<Dynamic_Event>& dyn_events);

void add_retriggers(
    Grid_Cell& grid_cell,
    Time_Data& time_data,
    std::vector<Dynamic_Event>& dyn_events
);

bool edge_trigger(Time_Data& time_data);

bool should_event_trigger(Grid_Cell& grid_cell);

int get_tick(Time_Data& time_data);

struct Get_Ticks_Res
{
	int tick;
	int prev_tick;
};

Get_Ticks_Res get_ticks(Time_Data& time_data);
