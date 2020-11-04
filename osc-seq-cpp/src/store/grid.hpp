#pragma once
#include <vector>

struct Grid_Cell {
    bool toggled;
    Grid_Cell();
};

struct Grid {
    std::vector<std::vector<Grid_Cell>> data;

    Grid();
    Grid(int rows, int cols);
};
