#pragma once

#include <functional>
#include <string>
#include <vector>

#include "grid.hpp"
#include "grid_cell.hpp"
#include "pattern_grid_cell.hpp"

struct Seq_Grid
{
    int selected_row;
    int selected_col;

    int selected_target_row;
    int selected_target_col;

    Event_Grid clock_grid;
    Event_Grid clickable_grid;

    Seq_Grid() {}
    Seq_Grid(int numRows, int numCols, int rect_w, int rect_h);
    Grid_Cell& get_selected();
    void set_selected(int row, int col, bool lshift);
    void add_row();
    void pop_row();
};
