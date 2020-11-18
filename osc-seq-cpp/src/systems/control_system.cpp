#include "control_system.hpp"

#include <iostream>

#include "../util.hpp"
#include "../store/grid_cell.hpp"

void control_system(Store& store)
{
    if (store.ui_state.keydown_event) {
        control_grid_selection_system(
            store.seq_grid,
            store.event_editor,
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
    Event_Editor& event_editor,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
) {
    Grid_Cell& grid_cell = seq_grid.get_selected();

    if (is_event(Event::Space, ui_state, prev_ui_state)) {
        if (!grid_cell.toggled) {
            grid_cell.toggled = true;
            if (ui_state.lshift) {
                grid_cell.has_meta = true;
            }
        } else if (grid_cell.toggled) {
            if (ui_state.lshift && !grid_cell.has_meta) {
                grid_cell.has_meta = true;
            } else {
                grid_cell.toggled = false;
                grid_cell.has_meta = false;
                event_editor.cur_selected_field = 0;
            }
        }
        return;
    }

    if (ui_state.up) {
        seq_grid.selection_row = clamp(seq_grid.selection_row - 1, 0, seq_grid.numRows);
    }
    if (ui_state.down) {
        seq_grid.selection_row = clamp(seq_grid.selection_row + 1, 0, seq_grid.numRows);
    }
    if (ui_state.right) {
        seq_grid.selection_col = clamp(seq_grid.selection_col + 1, 0, seq_grid.numCols);
    }
    if (ui_state.left) {
        seq_grid.selection_col = clamp(seq_grid.selection_col - 1, 0, seq_grid.numCols);
    }
}

void control_event_editor_system(
    Seq_Grid& seq_grid,
    Event_Editor& event_editor,
    Ui_State& ui_state
) {
    Grid_Cell& grid_cell = seq_grid.get_selected();

    // move selector up and down
    int len = grid_cell.data.size();
    if (grid_cell.has_meta) {
        len += grid_cell.meta_data.size();
    }

    if (ui_state.w) {
        event_editor.cur_selected_field = clamp(
            event_editor.cur_selected_field - 1, 0, len
        );
    } else if (ui_state.s) {
        event_editor.cur_selected_field = clamp(
            event_editor.cur_selected_field + 1, 0, len
        );
    }

    // NEW
    if (event_editor.cur_selected_field < grid_cell.data.size()) {
        if (ui_state.a) {
            grid_cell.data[event_editor.cur_selected_field].decrement();
        } else if (ui_state.d) {
            grid_cell.data[event_editor.cur_selected_field].increment();
        }
    }

    // OLD
    // // increase or decrease row value
    // int amount = 10;
    // if (event_editor.cur_selected_field == 0) {
    //     if (ui_state.a) {
    //         grid_cell.probability = clamp(
    //             grid_cell.probability - amount, 0, 101
    //         );
    //     } else if (ui_state.d) {
    //         grid_cell.probability = clamp(
    //             grid_cell.probability + amount, 0, 101
    //         );
    //     }
    // } else if (event_editor.cur_selected_field == 1) {
    //     if (ui_state.a) {
    //         grid_cell.retrigger = clamp(grid_cell.retrigger - 1, 1, 101);
    //     } else if (ui_state.d) {
    //         grid_cell.retrigger = clamp(grid_cell.retrigger + 1, 1, 101);
    //     }
    // } else if (
    //     event_editor.cur_selected_field >= grid_cell.num_fields
    //     && event_editor.cur_selected_field < grid_cell.num_fields + grid_cell.data.size()
    // ) {
    //     int i = event_editor.cur_selected_field - grid_cell.num_fields;
    //     auto& row = grid_cell.data[i];
    //     if (ui_state.a) {
    //         row.value = clamp(row.value - 1, row.min, row.max);
    //     } else if (ui_state.d) {
    //         row.value = clamp(row.value + 1, row.min, row.max);
    //     }
    // }
}

