#include "pattern_grid.hpp"
#include <iostream>

Pattern_Grid::Pattern_Grid(int num_rows, int num_cols, int rect_w, int rect_h)
    : selected_row(0), selected_col(0), num_rows(num_rows), num_cols(num_cols)
{
    grid = Grid<Pattern_Grid_Cell>(num_rows, num_cols, rect_w, rect_h);
    for (auto& row : grid.data) {
        for (auto& elt : row) {
            elt.toggled = false;
        }
    }
    grid.data[selected_row][selected_col].toggled = true;
}

void Pattern_Grid::set_selected(int row, int col)
{
    grid.for_each([&] (auto& elt, int, int) {
        elt.toggled = false;
    });
    selected_row = row;
    selected_col = col;
    grid.data[row][col].toggled = true;
}
