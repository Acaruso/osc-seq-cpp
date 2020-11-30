#include "seq_grid.hpp"

Seq_Grid::Seq_Grid(int numRows, int numCols, int rect_w, int rect_h)
    : selected_row(0), selected_col(0),
    selected_target_row(0), selected_target_col(0)
{
    int clock_grid_rect_h = rect_h / 2;

    clock_grid = Event_Grid(1, numCols, rect_w, clock_grid_rect_h);

    clickable_grid = Event_Grid(numRows, numCols, rect_w, rect_h);

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            auto& elt = clickable_grid.data[row][col];
            elt.channel = row;
        }
    }
}

Grid_Cell& Seq_Grid::get_selected()
{
    return clickable_grid.data[selected_row][selected_col];
}

void Seq_Grid::set_selected(int row, int col, bool lshift)
{
    auto& grid_cell = clickable_grid.data[row][col];
    if (!lshift) {
        grid_cell.toggled = !grid_cell.toggled;
        if (!grid_cell.toggled) {
            grid_cell.init_all_event_fields();
        }
        if (grid_cell.toggled) {
            auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
            target.first.data = row;
            target.second.data = col;
        }
    }
    selected_row = row;
    selected_col = col;
}

void Seq_Grid::add_row()
{
    int channel = clickable_grid.data.size();

    std::vector<Grid_Cell> v;
    for (int k = 0; k < clickable_grid.numCols; k++) {
        v.push_back(Grid_Cell(channel));
    }
    clickable_grid.data.push_back(v);
    ++clickable_grid.numRows;
}

void Seq_Grid::pop_row()
{
    if (clickable_grid.numRows == 1) {
        return;
    } else {
        clickable_grid.data.pop_back();
        --clickable_grid.numRows;
    }
}
