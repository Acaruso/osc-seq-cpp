#pragma once
#include <vector>

struct Grid_Cell {
    bool toggled;
    Grid_Cell();
};

struct Grid {
    int x;
    int y;
    int numRows;
    int numCols;
    std::vector<std::vector<Grid_Cell>> data;

    Grid();
    Grid(int x, int y, int numRows, int numCols);
    void print();
};
