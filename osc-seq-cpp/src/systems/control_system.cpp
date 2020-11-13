#include "control_system.hpp"

#include <iostream>

void control_system(Store& store) {
    // control_rect_system(store.rect, store.ui_state);

    if (store.ui_state.keydown_event) {
        control_grid_selection_system(
            store.seq_grid.selection_row,
            store.seq_grid.selection_col,
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
    int& selection_row,
    int& selection_col,
    Ui_State& ui_state
) {
    if (ui_state.up) {
        selection_row -= 1;
    }
    if (ui_state.down) {
        selection_row += 1;
    }
    if (ui_state.right) {
        selection_col += 1;
    }
    if (ui_state.left) {
        selection_col -= 1;
    }
}
