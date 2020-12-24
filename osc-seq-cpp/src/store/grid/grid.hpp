#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "grid_cell.hpp"
#include "pattern_grid_cell.hpp"

template <typename T>
struct Grid
{
    int numRows;
    int numCols;
    int rect_w;
    int rect_h;
    std::vector<std::vector<T>> data;

    Grid() {}

    Grid(int numRows, int numCols, int rect_w, int rect_h)
    : numRows(numRows), numCols(numCols), rect_w(rect_w), rect_h(rect_h)
    {
        for (int row = 0; row < numRows; ++row) {
            std::vector<T> v;
            for (int col = 0; col < numCols; ++col) {
                v.push_back(T{});
            }
            data.push_back(v);
        }
    }

    void for_each(std::function<void(T&, int, int)> fn)
    {
        for (int i = 0; i < numRows; i++) {
            for (int k = 0; k < numCols; k++) {
                T& elt = data[i][k];
                fn(elt, i, k);
            }
        }
    }
};

using Event_Grid = Grid<Grid_Cell>;
