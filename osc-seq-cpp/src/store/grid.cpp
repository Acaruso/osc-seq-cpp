#include "grid.hpp"

Grid::Grid() {}

Grid::Grid(int numRows, int numCols, int rect_w, int rect_h)
    : numRows(numRows), numCols(numCols), rect_w(rect_w), rect_h(rect_h)
{
    for (int i = 0; i < numRows; i++) {
        std::vector<Grid_Cell> v;
        for (int k = 0; k < numCols; k++) {
            v.push_back(Grid_Cell());
        }
        data.push_back(v);
    }
}

void Grid::print()
{
    for (auto& row : data) {
        for (auto& col : row) {
            printf("%d", col.toggled);
        }
        printf("\n");
    }
    printf("\n");
}

Seq_Grid::Seq_Grid() {}

Seq_Grid::Seq_Grid(int numRows, int numCols, int rect_w, int rect_h)
    : numRows(numRows), numCols(numCols), rect_w(rect_w), rect_h(rect_h),
    selection_row(0), selection_col(0)
{
    int clock_grid_rect_h = rect_h / 2;

    clock_grid = Grid(1, numCols, rect_w, clock_grid_rect_h);

    clickable_grid = Grid(numRows, numCols, rect_w, rect_h);
}

Grid_Cell& Seq_Grid::get_selected()
{
    return clickable_grid.data[selection_row][selection_col];
}

void Seq_Grid::add_row()
{
    std::vector<Grid_Cell> v;
    for (int k = 0; k < clickable_grid.numCols; k++) {
        v.push_back(Grid_Cell());
    }
    clickable_grid.data.push_back(v);
    ++clickable_grid.numRows;
    ++numRows;
}

void Seq_Grid::pop_row()
{
    if (clickable_grid.numRows == 1) {
        return;
    } else {
        clickable_grid.data.pop_back();
        --clickable_grid.numRows;
        --numRows;
    }
}
