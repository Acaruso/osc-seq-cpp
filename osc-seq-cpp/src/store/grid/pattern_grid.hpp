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

    Grid<Pattern_Grid_Cell> grid;

    Pattern_Grid() {}
    Pattern_Grid(int numRows, int numCols, int rect_w, int rect_h);
    // Grid_Cell& get_selected();
};
