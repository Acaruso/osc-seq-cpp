#pragma once

#include <functional>
#include <string>
#include <vector>

#include "grid.hpp"
#include "pattern_grid_cell.hpp"

struct Pattern_Grid
{
    int selected_row;
    int selected_col;

    int num_rows;
    int num_cols;

    Grid<Pattern_Grid_Cell> grid;

    Pattern_Grid() {}

    Pattern_Grid(int num_rows, int num_cols, int rect_w, int rect_h);

    void set_selected(int row, int col);

    void increment_selected_row();

    void decrement_selected_row();

    void increment_selected_col();

    void decrement_selected_col();

    void clear_and_set_toggled(int row, int col);
};
