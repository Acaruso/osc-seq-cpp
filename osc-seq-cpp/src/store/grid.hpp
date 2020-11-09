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
    int rect_w;
    int rect_h;
    std::vector<std::vector<Grid_Cell>> data;

    Grid();
    Grid(int x, int y, int numRows, int numCols, int rect_w, int rect_h);
    void print();
};

struct Seq_Grid {
    int x;
    int y;
    int numRows;
    int numCols;
    int rect_w;
    int rect_h;

    Grid clock_grid;
    Grid clickable_grid;

    Seq_Grid();
    Seq_Grid(int x, int y, int numRows, int numCols, int rect_w, int rect_h);
};