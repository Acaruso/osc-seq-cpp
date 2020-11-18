#pragma once

#include <string>
#include <vector>

#include "grid_cell.hpp"

struct Grid
{
    int numRows;
    int numCols;
    int rect_w;
    int rect_h;
    std::vector<std::vector<Grid_Cell>> data;

    Grid();
    Grid(int numRows, int numCols, int rect_w, int rect_h);
};

struct Seq_Grid
{
    int numRows;
    int numCols;
    int rect_w;
    int rect_h;
    int selection_row;
    int selection_col;

    Grid clock_grid;
    Grid clickable_grid;

    Seq_Grid();
    Seq_Grid(int numRows, int numCols, int rect_w, int rect_h);
    Grid_Cell& get_selected();
    void add_row();
    void pop_row();
};
