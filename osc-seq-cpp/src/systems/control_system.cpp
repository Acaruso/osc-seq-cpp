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
            store.event_editor,
            store.ui_state
        );
    }
}

void control_grid_selection_system(
    Seq_Grid& seq_grid,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
) {
    Grid_Cell& grid_cell = seq_grid.get_selected();

    if (is_event(Event::Space, ui_state, prev_ui_state)) {
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

int clamp(int x, int min, int max);

void control_event_editor_system(
    Seq_Grid& seq_grid,
    Event_Editor& event_editor,
    Ui_State& ui_state
) {
    Grid_Cell& grid_cell = seq_grid.get_selected();

    int len = grid_cell.data.size() + 2;

    if (ui_state.w) {
        event_editor.cur_selected_field = clamp(
            event_editor.cur_selected_field - 1, 0, len
        );
    } else if (ui_state.s) {
        event_editor.cur_selected_field = clamp(
            event_editor.cur_selected_field + 1, 0, len
        );
    }

    int amount = 10;
    if (event_editor.cur_selected_field == 0) {
        if (ui_state.a) {
            grid_cell.probability = clamp(
                grid_cell.probability - amount, 0, 101
            );
        } else if (ui_state.d) {
            grid_cell.probability = clamp(
                grid_cell.probability + amount, 0, 101
            );
        }
    } else if (event_editor.cur_selected_field == 1) {
        if (ui_state.a) {
            grid_cell.retrigger = clamp(grid_cell.retrigger - 1, 1, 101);
        } else if (ui_state.d) {
            grid_cell.retrigger = clamp(grid_cell.retrigger + 1, 1, 101);
        }
    }
}

int clamp(int x, int min, int max) {
    if (x < min) {
        return min;
    } else if ( x >= max) {
        return max - 1;
    } else {
        return x;
    }
}
