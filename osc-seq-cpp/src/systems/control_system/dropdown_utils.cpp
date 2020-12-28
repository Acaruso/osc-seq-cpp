#include "dropdown_utils.hpp"

#include "../../store/grid/grid_cell.hpp"
#include "../../store/grid/grid_cell_fields.hpp"
#include "../../util.hpp"

#include <variant>

void toggle_dropdown_mode(Store& store)
{
    auto& grid_cell = store.seq_grid.get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(store.event_editor);
    auto& subfield = field.get_selected_subfield(store.event_editor);
    if (has_dropdown(subfield)) {
        auto& v = std::get<Options_Subfield>(subfield);
        if (store.ui_state.mode == Normal) {
            store.event_editor.selected_dropdown_row = v.selected;
            store.ui_state.mode = Dropdown;
        } else {
            // store.event_editor.prev_dropdown_rows.clear();
            v.selected = store.event_editor.selected_dropdown_row;
            store.ui_state.mode = Normal;
        }
    }
}

void increment_dropdown_row(Store& store)
{
    auto& grid_cell = store.seq_grid.get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(store.event_editor);
    auto& subfield = field.get_selected_subfield(store.event_editor);

    if (has_dropdown(subfield)) {
        auto& v = std::get<Options_Subfield>(subfield);
        increment(
            store.event_editor.selected_dropdown_row,
            0,
            grid_cell.get_dropdown_list(v).size()
        );
    }
}

void decrement_dropdown_row(Store& store)
{
    auto& grid_cell = store.seq_grid.get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(store.event_editor);
    auto& subfield = field.get_selected_subfield(store.event_editor);

    if (has_dropdown(subfield)) {
        auto& v = std::get<Options_Subfield>(subfield);
        decrement(
            store.event_editor.selected_dropdown_row,
            0,
            grid_cell.get_dropdown_list(v).size()
        );
    }
}

void increment_dropdown_col(Store& store)
{
    auto& ee = store.event_editor;
    auto& grid_cell = store.seq_grid.get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(ee);
    auto& subfield = field.get_selected_subfield(ee);

    if (has_dropdown(subfield)) {
        auto& v = std::get<Options_Subfield>(subfield);
        auto dd_list = grid_cell.get_dropdown_list(v);
        auto& selected_entry = dd_list[ee.selected_dropdown_row];
        int depth = selected_entry.subentries.empty() ? 0 : 1;

        if (ee.selected_dropdown_col < depth + 1) {
            ee.prev_dropdown_rows.push_back(ee.selected_dropdown_row);
            increment(ee.selected_dropdown_col, 0, depth + 1);
        }
    }
}

void decrement_dropdown_col(Store& store)
{
    auto& ee = store.event_editor;
    auto& grid_cell = store.seq_grid.get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(store.event_editor);
    auto& subfield = field.get_selected_subfield(store.event_editor);

    if (has_dropdown(subfield)) {
        auto& v = std::get<Options_Subfield>(subfield);
        auto dd_list = grid_cell.get_dropdown_list(v);
        auto& selected_entry = dd_list[store.event_editor.selected_dropdown_row];
        int depth = selected_entry.subentries.empty() ? 0 : 1;

        if (ee.selected_col > 0) {
            ee.prev_dropdown_rows.pop_back();
            decrement(ee.selected_dropdown_col, 0, depth + 1);
        }
    }
}
