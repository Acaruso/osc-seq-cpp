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
            auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
            target.first.data = seq_grid.selected_row;
            target.second.data = seq_grid.selected_col;

            if (ui_state.lshift) {
                grid_cell.has_meta = true;
            }
        } else if (grid_cell.toggled) {
            if (ui_state.lshift && !grid_cell.has_meta) {
                grid_cell.has_meta = true;
            } else {
                grid_cell.toggled = false;
                grid_cell.has_meta = false;
                event_editor.selected_row = 0;
                ui_state.mode = Normal;
            }
        }
        return;
    }

    if (is_event(Event::Tab, ui_state, prev_ui_state)) {
        event_editor.selected_col = (event_editor.selected_col + 1) % 2;
    }

    if (ui_state.up || ui_state.down || ui_state.left || ui_state.right) {
        if (ui_state.mode == Normal) {
            if (ui_state.up) {
                seq_grid.selected_row = clamp(
                    seq_grid.selected_row - 1,
                    0,
                    seq_grid.numRows
                );
            }
            if (ui_state.down) {
                seq_grid.selected_row = clamp(
                    seq_grid.selected_row + 1,
                    0,
                    seq_grid.numRows
                );
            }
            if (ui_state.right) {
                seq_grid.selected_col = clamp(
                    seq_grid.selected_col + 1,
                    0,
                    seq_grid.numCols
                );
            }
            if (ui_state.left) {
                seq_grid.selected_col = clamp(
                    seq_grid.selected_col - 1,
                    0,
                    seq_grid.numCols
                );
            }
            event_editor.selected_row = 0;
        } else if (ui_state.mode == Target_Select) {
            if (ui_state.up) {
                seq_grid.selected_target_row = clamp(
                    seq_grid.selected_target_row - 1,
                    0,
                    seq_grid.numRows
                );
            }
            if (ui_state.down) {
                seq_grid.selected_target_row = clamp(
                    seq_grid.selected_target_row + 1,
                    0,
                    seq_grid.numRows
                );
            }
            if (ui_state.right) {
                seq_grid.selected_target_col = clamp(
                    seq_grid.selected_target_col + 1,
                    0,
                    seq_grid.numCols
                );
            }
            if (ui_state.left) {
                seq_grid.selected_target_col = clamp(
                    seq_grid.selected_target_col - 1,
                    0,
                    seq_grid.numCols
                );
            }

            auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
            target.first.data = seq_grid.selected_target_row;
            target.second.data = seq_grid.selected_target_col;
        }
    }
}

void control_event_editor_system(
    Seq_Grid& seq_grid,
    Event_Editor& ee,
    Ui_State& ui_state
) {
    Grid_Cell& grid_cell = seq_grid.get_selected();

    if (!grid_cell.toggled) {
        return;
    }

    int len = grid_cell.fields.size() + grid_cell.meta_fields.size();

    // move selector up or down
    if (ui_state.w || ui_state.s) {
        if (ui_state.w) {
            ee.selected_row = clamp(ee.selected_row - 1, 0, len);
        } else if (ui_state.s) {
            ee.selected_row = clamp(ee.selected_row + 1, 0, len);
        }

        auto& new_field = grid_cell.get_selected_event(ee);

        if (new_field.key == "target") {
            ui_state.mode = Target_Select;
            auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
            seq_grid.selected_target_row = target.first.data;
            seq_grid.selected_target_col = target.second.data;
        } else {
            ui_state.mode = Normal;
        }
    }

    // increment or decrement currently selected field
    auto& field = grid_cell.get_selected_event(ee);
    if (field.key != "target") {
        if (ui_state.a) {
            field.decrement(ee);
        } else if (ui_state.d) {
            field.increment(ee);
        }
    }
}
