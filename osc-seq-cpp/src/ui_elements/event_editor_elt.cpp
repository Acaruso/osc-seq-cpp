#include "event_editor_elt.hpp"

#include <iostream>
#include <string>

#include "dropdown_elt.hpp"
#include "event_editor_tabs_elt.hpp"
#include "image_elt.hpp"
#include "text_elt.hpp"

void event_editor_wrapper_elt(
    Coord& coord,
    Store& store
) {
    if (store.event_editor.mode == Event_Editor_Mode::Normal) {
        Grid_Cell& grid_cell = store.seq_grid.get_selected_cell();

        text_elt("Event Editor", coord, store);

        Coord tabs_coord = { coord.x, coord.y + store.line_height };
        event_editor_tabs_elt(grid_cell, tabs_coord, store);

        Coord body_coord = { coord.x, tabs_coord.y + store.line_height };
        event_editor_body_elt(grid_cell, body_coord, store);

        event_editor_selector_elt(grid_cell, coord, store);
    } else if (store.event_editor.mode == Event_Editor_Mode::Set_Default_Values) {
        Grid_Cell& grid_cell = store.seq_grid.get_default_grid_cell();

        text_elt("Default Values", coord, store);

        Coord tabs_coord = { coord.x, coord.y + store.line_height };
        event_editor_tabs_elt(grid_cell, tabs_coord, store);

        Coord body_coord = { coord.x, tabs_coord.y + store.line_height };
        event_editor_body_elt(grid_cell, body_coord, store);

        event_editor_selector_elt(grid_cell, coord, store);
    }
}

void event_editor_selector_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    Coord select_coord = {
        coord.x - store.line_height,
        coord.y + (store.line_height * 2) + (store.line_height * store.event_editor.selected_row)
    };

    image_elt(store.images["select-event-editor"], select_coord, store);
}

void event_editor_body_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    auto& fields = grid_cell.get_selected_tab(store.event_editor).fields;
    int i = 0;

    for (auto& field : fields) {
        event_editor_row_elt(field, grid_cell, coord, i++, store);
    }
}

void event_editor_row_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    Coord& coord,
    int index,
    Store& store
) {
    std::string text = grid_cell.toggled
        ? field.key + ": " + field.get_display().text
        : field.key + ": ";

    Coord row_coord = {
        coord.x,
        coord.y + (index * store.line_height)
    };

    text_elt(text, row_coord, store);

    if (should_show_underline(field, grid_cell, index, store.event_editor)) {
        underline_elt(
            field,
            row_coord,
            store
        );
    }

    if (should_show_dropdown(field, grid_cell, index, store.event_editor, store.ui_state)) {
        dropdown_elt(field, grid_cell, row_coord, store);
    }
}

bool should_show_underline(
    Event_Field& field,
    Grid_Cell& grid_cell,
    int index,
    Event_Editor& ee
) {
    return (grid_cell.toggled && field.get_num_selectable_subfields() > 1 && ee.selected_row == index);
}

bool should_show_dropdown(
    Event_Field& field,
    Grid_Cell& grid_cell,
    int index,
    Event_Editor& ee,
    Ui_State& ui_state
) {
    if (ee.selected_row != index) {
        return false;
    }

    auto& subfield = field.get_selected_subfield(ee);

    // bool has_dropdown = (std::get_if<Options_Subfield>(&subfield) != 0);

    return (
        grid_cell.toggled
        && ee.selected_row == index
        && ui_state.mode == Dropdown
        && has_dropdown(subfield)
    );
}

void underline_elt(
    Event_Field& field,
    Coord& coord,
    Store& store
) {
    auto value_display_res = field.get_display();
    auto& idxs = value_display_res.subfield_idxs[store.event_editor.selected_col];

    for (int i = idxs.first; i < idxs.second; ++i) {
        Coord underline_coord = {
            coord.x + (i * store.font_width),
            coord.y + 14
        };

        image_elt(store.images["select-underline"], underline_coord, store);
    }
}
