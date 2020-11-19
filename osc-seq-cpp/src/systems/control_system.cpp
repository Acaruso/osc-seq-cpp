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
        seq_grid.selected_row = clamp(seq_grid.selected_row - 1, 0, seq_grid.numRows);
    }
    if (ui_state.down) {
        seq_grid.selected_row = clamp(seq_grid.selected_row + 1, 0, seq_grid.numRows);
    }
    if (ui_state.right) {
        seq_grid.selected_col = clamp(seq_grid.selected_col + 1, 0, seq_grid.numCols);
    }
    if (ui_state.left) {
        seq_grid.selected_col = clamp(seq_grid.selected_col - 1, 0, seq_grid.numCols);
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
    int num_meta_data_rows = 1;
    if (grid_cell.has_meta) {
        len += num_meta_data_rows;
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

    // increment or decrement value
    if (event_editor.cur_selected_field < grid_cell.data.size()) {
        if (ui_state.a) {
            grid_cell.data[event_editor.cur_selected_field].decrement();
        } else if (ui_state.d) {
            grid_cell.data[event_editor.cur_selected_field].increment();
        }
    } else if (event_editor.cur_selected_field >= grid_cell.data.size()) {
        int idx = event_editor.cur_selected_field - grid_cell.data.size();
        if (idx == 0) { // num targets
            auto& targets = grid_cell.get_meta_data("targets").targets;
            if (ui_state.a) {
                if (targets.size() > 0) {
                    grid_cell.get_meta_data("targets").targets.pop_back();
                }
            } else if (ui_state.d) {
                targets.push_back({ -1, -1 });
            }
        }
    }
}
