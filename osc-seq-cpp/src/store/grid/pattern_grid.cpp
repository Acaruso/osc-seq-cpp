#include "pattern_grid.hpp"
#include <iostream>

Pattern_Grid::Pattern_Grid(int numRows, int numCols, int rect_w, int rect_h)
    : selected_row(0), selected_col(0)
{
    std::cout << "constructor" << std::endl;
    grid = Grid<Pattern_Grid_Cell>(numRows, numCols, rect_w, rect_h);
    for (auto& row : grid.data) {
        for (auto& elt : row) {
            std::cout << "test" << std::endl;
            elt.toggled = false;
        }
    }
}
