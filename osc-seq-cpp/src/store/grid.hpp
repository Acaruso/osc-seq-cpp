#pragma once

#include <string>
#include <vector>

struct Grid_Cell_Data
{
    std::string key;
    int value;
    int min;
    int max;
};

struct Grid_Cell
{
    bool toggled;
    int probability;
    int retrigger;
    std::vector<Grid_Cell_Data> data;
    Grid_Cell();
};

struct Grid
{
    int numRows;
    int numCols;
    int rect_w;
    int rect_h;
    std::vector<std::vector<Grid_Cell>> data;

    Grid();
    Grid(int numRows, int numCols, int rect_w, int rect_h);
    void print();
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
