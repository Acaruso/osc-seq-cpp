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
                event_editor.selected_row = 0;
            }
        }
        return;
    }

    if (is_event(Event::Tab, ui_state, prev_ui_state)) {
        event_editor.selected_col = (event_editor.selected_col + 1) % 2;
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

void inc_field(Event_Field& field, Event_Editor& event_editor);
void dec_field(Event_Field& field, Event_Editor& event_editor);

void control_event_editor_system(
    Seq_Grid& seq_grid,
    Event_Editor& event_editor,
    Ui_State& ui_state
) {
    Grid_Cell& grid_cell = seq_grid.get_selected();

    // move selector up and down
    int len = grid_cell.fields.size() + grid_cell.meta_fields.size();

    if (ui_state.w) {
        event_editor.selected_row = clamp(
            event_editor.selected_row - 1, 0, len
        );
    } else if (ui_state.s) {
        event_editor.selected_row = clamp(
            event_editor.selected_row + 1, 0, len
        );
    }

    // inc dec value
    auto& field = grid_cell.get_selected_event(event_editor);
    if (ui_state.a) {
        dec_field(field, event_editor);
    } else if (ui_state.d) {
        inc_field(field, event_editor);
    }
}

void inc_field(Event_Field& field, Event_Editor& event_editor)
{
    switch (field.value.index()) {
    case 0:
    {
        auto& x = std::get<Int_Field>(field.value);
        x.data = clamp(x.data + 1, x.min, x.max);
        return;
    }
    case 1:
    {
        auto& x = std::get<Int_Pair_Field>(field.value);
        if (event_editor.selected_col == 0) {
            x.first.data = clamp(x.first.data + 1, x.first.min, x.first.max);
        } else if (event_editor.selected_col == 1) {
            x.second.data = clamp(x.second.data + 1, x.second.min, x.second.max);
        }
        return;
    }
    }
}

void dec_field(Event_Field& field, Event_Editor& event_editor)
{
    switch (field.value.index()) {
    case 0:
    {
        auto& x = std::get<Int_Field>(field.value);
        x.data = clamp(x.data - 1, x.min, x.max);
        return;
    }
    case 1:
    {
        auto& x = std::get<Int_Pair_Field>(field.value);
        if (event_editor.selected_col == 0) {
            x.first.data = clamp(x.first.data - 1, x.first.min, x.first.max);
        } else if (event_editor.selected_col == 1) {
            x.second.data = clamp(x.second.data - 1, x.second.min, x.second.max);
        }
        return;
    }
    }
}
