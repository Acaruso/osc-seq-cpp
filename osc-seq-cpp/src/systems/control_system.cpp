#include "control_system.hpp"

#include <iostream>

void control_system(Store& store) {
    // control_rect_system(store.rect, store.ui_state);

    if (store.ui_state.keydown_event) {
        control_grid_selection_system(
            store.seq_grid,
            store.ui_state
        );
    }
}

void control_rect_system(Rect& rect, Ui_State& ui_state) {
    int movement_amount = 3;

    if (ui_state.up) {
        rect.y -= movement_amount;
    }
    if (ui_state.down) {
        rect.y += movement_amount;
    }
    if (ui_state.right) {
        rect.x += movement_amount;
    }
    if (ui_state.left) {
        rect.x -= movement_amount;
    }
}

void control_grid_selection_system(
    Seq_Grid& seq_grid,
    Ui_State& ui_state
) {
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
    if (ui_state.space) {
        int row = seq_grid.selection_row;
        int col = seq_grid.selection_col;
        bool toggled = seq_grid.clickable_grid.data[row][col].toggled;
        seq_grid.clickable_grid.data[row][col].toggled = !toggled;
    }
}
