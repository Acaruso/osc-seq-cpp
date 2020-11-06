#pragma once
#include "rect.hpp"
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
    std::vector<std::vector<Rect>> data;

    Grid();
    Grid(int x, int y, int numRows, int numCols);
    void print();
};
