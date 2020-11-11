#pragma once

#include "../store/store.hpp"

void update_system(Store& store);

void update_clock_grid_system(Grid& grid, int clock, int step_len, int max_seq_len);

void send_osc_system(Grid& grid, int clock, int step_len, int max_seq_len);

struct Get_Ticks_Res {
	int tick;
	int prev_tick;
};

Get_Ticks_Res get_ticks(int clock, int step_len, int seq_len, int max_seq_len);
