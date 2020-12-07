#include "pattern_grid.hpp"

#include "../../util.hpp"

#include <iostream>

Pattern_Grid::Pattern_Grid(int num_rows, int num_cols, int rect_w, int rect_h)
    : selected_row(0), selected_col(0), selected_copy_row(0), selected_copy_col(0),
    num_rows(num_rows), num_cols(num_cols)
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
    selected_row = row;
    selected_col = col;
    // clear_and_set_toggled(selected_row, selected_col);
}

void Pattern_Grid::increment_selected_row()
{
    increment(selected_row, 0, num_rows);
    selected_copy_row = selected_row;
    // clear_and_set_toggled(selected_row, selected_col);
}

void Pattern_Grid::decrement_selected_row()
{
    decrement(selected_row, 0, num_rows);
    selected_copy_row = selected_row;
    // clear_and_set_toggled(selected_row, selected_col);
}

void Pattern_Grid::increment_selected_col()
{
    increment(selected_col, 0, num_cols);
    selected_copy_col = selected_col;
    // clear_and_set_toggled(selected_row, selected_col);
}

void Pattern_Grid::decrement_selected_col()
{
    decrement(selected_col, 0, num_cols);
    selected_copy_col = selected_col;
    // clear_and_set_toggled(selected_row, selected_col);
}

void Pattern_Grid::clear_and_set_toggled(int row, int col)
{
    // grid.for_each([&] (auto& elt, int, int) {
    //     elt.toggled = false;
    // });
    // grid.data[row][col].toggled = true;

    selected_copy_row = row;
    selected_copy_col = col;
}

void Pattern_Grid::increment_selected_copy_row()
{
    increment(selected_copy_row, 0, num_rows);
}

void Pattern_Grid::decrement_selected_copy_row()
{
    decrement(selected_copy_row, 0, num_rows);
}

void Pattern_Grid::increment_selected_copy_col()
{
    increment(selected_copy_col, 0, num_cols);
}

void Pattern_Grid::decrement_selected_copy_col()
{
    decrement(selected_copy_col, 0, num_cols);
}
