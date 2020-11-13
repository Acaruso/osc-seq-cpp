#include "control_system.hpp"

#include <iostream>

#include "../util.hpp"

void control_system(Store& store) {
    if (store.ui_state.keydown_event) {
        control_grid_selection_system(
            store.seq_grid,
            store.ui_state,
            store.prev_ui_state
        );
    }
}

void control_grid_selection_system(
    Seq_Grid& seq_grid,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
) {
    if (is_event(Event::Space, ui_state, prev_ui_state)) {
        int row = seq_grid.selection_row;
        int col = seq_grid.selection_col;
        bool toggled = seq_grid.clickable_grid.data[row][col].toggled;
        seq_grid.clickable_grid.data[row][col].toggled = !toggled;
        return;
    }

    if (ui_state.up && seq_grid.selection_row - 1 >= 0) {
        seq_grid.selection_row -= 1;
    }
    if (ui_state.down && seq_grid.selection_row + 1 < seq_grid.numRows) {
        seq_grid.selection_row += 1;
    }
    if (ui_state.right && seq_grid.selection_col + 1 < seq_grid.numCols) {
        seq_grid.selection_col += 1;
    }
    if (ui_state.left && seq_grid.selection_col - 1 >= 0) {
        seq_grid.selection_col -= 1;
    }
}
