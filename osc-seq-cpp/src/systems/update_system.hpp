#pragma once

#include <vector>

#include "../store/store.hpp"

struct Time_Data {
    int clock;
    int steps_per_seq;
    int frames_per_step;
    int frames_per_seq;
};

struct Retrigger {
    // Time_Data time_data;
    int time_to_trigger;
    int channel;
};

void update_system(Store& store);

void update_clock_grid_system(Grid& grid, Time_Data& time_data);

void handle_event_system(
    Grid& grid,
    Time_Data& time_data,
    std::vector<Retrigger>& retriggers
);

void handle_retriggers_system(int clock, std::vector<Retrigger>& retriggers);

void add_retriggers(
    Grid_Cell& grid_cell,
    int channel,
    Time_Data& time_data,
    std::vector<Retrigger>& retriggers
);

bool edge_trigger(Time_Data& time_data);

bool should_event_trigger(Grid_Cell& grid_cell);

int get_tick(Time_Data& time_data);

struct Get_Ticks_Res {
	int tick;
	int prev_tick;
};

Get_Ticks_Res get_ticks(Time_Data& time_data);
