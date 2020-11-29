#pragma once

#include <functional>
#include <string>
#include <vector>

#include "grid_cell.hpp"
#include "pattern_grid_cell.hpp"
#include "grid.hpp"

struct Seq_Grid
{
    int numRows;
    int numCols;

    int rect_w;
    int rect_h;

    int selected_row;
    int selected_col;

    int selected_target_row;
    int selected_target_col;

    Event_Grid clock_grid;
    Event_Grid clickable_grid;

    Seq_Grid() {}
    Seq_Grid(int numRows, int numCols, int rect_w, int rect_h);
    Grid_Cell& get_selected();
    void add_row();
    void pop_row();
};
