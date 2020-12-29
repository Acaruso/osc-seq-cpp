#include "dropdown_utils.hpp"

#include "../../store/grid/grid_cell.hpp"
#include "../../store/grid/grid_cell_fields.hpp"
#include "../../util.hpp"

#include <iostream>
#include <variant>

void toggle_dropdown_mode(Store& store)
{
    auto& ee = store.event_editor;
    auto& grid_cell = store.seq_grid.get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(ee);
    auto& subfield = field.get_selected_subfield(ee);

    if (has_dropdown(subfield)) {
        auto& v = std::get<Options_Subfield>(subfield);
        if (store.ui_state.mode == Normal) {
            ee.selected_dropdown_col = 0;
            ee.selected_dropdown_rows[ee.selected_dropdown_col] = v.selected;
            store.ui_state.mode = Dropdown;
        } else {
            v.selected = ee.selected_dropdown_rows[ee.selected_dropdown_col];
            ee.selected_dropdown_col = 0;
            store.ui_state.mode = Normal;
        }
    }
}

void increment_dropdown_row(Store& store)
{
    auto& ee = store.event_editor;
    auto& grid_cell = store.seq_grid.get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(ee);
    auto& subfield = field.get_selected_subfield(ee);

    if (has_dropdown(subfield)) {
        auto& v = std::get<Options_Subfield>(subfield);
        auto dd_list = grid_cell.get_dropdown_list(v);
        Dropdown_Entry* parent = get_selected_dropdown_parent(dd_list, ee);

        increment(
            ee.selected_dropdown_rows[ee.selected_dropdown_col],
            0,
            parent->subentries.size()
        );
    }
}

void decrement_dropdown_row(Store& store)
{
    auto& ee = store.event_editor;
    auto& grid_cell = store.seq_grid.get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(store.event_editor);
    auto& subfield = field.get_selected_subfield(store.event_editor);

    if (has_dropdown(subfield)) {
        auto& v = std::get<Options_Subfield>(subfield);
        auto dd_list = grid_cell.get_dropdown_list(v);
        Dropdown_Entry* parent = get_selected_dropdown_parent(dd_list, ee);

        decrement(
            ee.selected_dropdown_rows[ee.selected_dropdown_col],
            0,
            parent->subentries.size()
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
        Dropdown_Entry* cur = get_selected_dropdown_entry(dd_list, ee);
        if (!cur->subentries.empty()) {
            ee.selected_dropdown_col++;
            ee.selected_dropdown_rows[ee.selected_dropdown_col] = 0;
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
        if (ee.selected_dropdown_col > 0) {
            ee.selected_dropdown_col--;
        }
    }
}

Dropdown_Entry* get_selected_dropdown_entry(
    Dropdown_Entry& dd_list,
    Event_Editor& ee
) {
    Dropdown_Entry* cur = &dd_list;
    int sel_row;
    for (int i = 0; i <= ee.selected_dropdown_col; ++i) {
        sel_row = ee.selected_dropdown_rows[i];
        cur = &(cur->subentries[sel_row]);
    }
    return cur;
}

Dropdown_Entry* get_selected_dropdown_parent(
    Dropdown_Entry& dd_list,
    Event_Editor& ee
) {
    Dropdown_Entry* cur = &dd_list;
    int sel_row;
    for (int i = 0; i < ee.selected_dropdown_col; ++i) {
        sel_row = ee.selected_dropdown_rows[i];
        cur = &(cur->subentries[sel_row]);
    }
    return cur;
}
