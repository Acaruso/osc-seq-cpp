#include "control_system.hpp"

#include <iostream>

#include "../util.hpp"
#include "../store/grid.hpp"

void control_system(Store& store) {
    if (store.ui_state.keydown_event) {
        control_grid_selection_system(
            store.seq_grid,
            store.ui_state,
            store.prev_ui_state
        );
        control_event_editor_system(
            store.seq_grid,
            store.ui_state
        );
    }
}

void control_grid_selection_system(
    Seq_Grid& seq_grid,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
) {
    if (is_event(Event::Space, ui_state, prev_ui_state)) {
        Grid_Cell& grid_cell = seq_grid.get_selected();
        grid_cell.toggled = !grid_cell.toggled;
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

void control_event_editor_system(
    Seq_Grid& seq_grid,
    Ui_State& ui_state
) {
    int amount = 10;
    Grid_Cell& grid_cell = seq_grid.get_selected();

    if (ui_state.a && grid_cell.probability - 1 >= 0) {
        grid_cell.probability -= amount;
    } else if (ui_state.d && grid_cell.probability + 1 <= 100) {
        grid_cell.probability += amount;
    }
}
