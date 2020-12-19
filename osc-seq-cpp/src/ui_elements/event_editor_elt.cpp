#include "event_editor_elt.hpp"

#include <iostream>
#include <string>

#include "event_editor_tabs_elt.hpp"
#include "image_elt.hpp"
#include "text_elt.hpp"

void event_editor_wrapper_elt(
    Coord& coord,
    Store& store
) {
    text_elt("Event Editor", coord, store);

    Coord tabs_coord = { coord.x, coord.y + store.line_height };
    event_editor_tabs_elt(tabs_coord, store);

    /*
    if (store.event_editor.mode == Event_Editor_Mode::Normal) {
        Grid_Cell& grid_cell = store.seq_grid.get_selected_cell();

        event_editor_selector_elt(grid_cell, coord, store);

        event_editor_elt(
            "Event Editor",
            grid_cell,
            coord,
            store
        );
    } else if (store.event_editor.mode == Event_Editor_Mode::Set_Default_Values) {
        Grid_Cell& grid_cell = store.seq_grid.get_default_grid_cell();

        event_editor_selector_elt(grid_cell, coord, store);

        event_editor_defaults_elt(
            "Default Values",
            grid_cell,
            coord,
            store
        );
    }
    */
}

void event_editor_selector_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    Coord select_coord = get_selector_coord(
        store.event_editor.selected_row,
        store.line_height,
        grid_cell,
        coord
    );

    image_elt(store.images["select-event-editor"], select_coord, store);
}

void event_editor_elt(
    std::string header,
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    text_elt(header, coord, store);

    int i = 0;

    for (auto& field : grid_cell.fields) {
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
        ? field.key + ": " + field.get_value_display_str().text
        : field.key + ": ";

    Coord row_coord = {
        coord.x,
        coord.y + store.line_height + (index * store.line_height)
    };

    text_elt(text, row_coord, store);

    if (grid_cell.toggled && should_show_underline(field, index, store.event_editor)) {
        underline_elt(
            field.get_value_display_str(),
            field,
            row_coord,
            store
        );
    }
}

void event_editor_defaults_elt(
    std::string header,
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    text_elt(header, coord, store);

    int i = 0;

    for (auto& field : grid_cell.fields) {
        event_editor_defaults_row_elt(field, grid_cell, coord, i++, store);
    }
}

void event_editor_defaults_row_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    Coord& coord,
    int index,
    Store& store
) {
    std::string text = field.key + ": " + field.get_value_display_str().text;

    Coord row_coord = {
        coord.x,
        coord.y + store.line_height + (index * store.line_height)
    };

    text_elt(text, row_coord, store);

    if (should_show_underline(field, index, store.event_editor)) {
        underline_elt(
            field.get_value_display_str(),
            field,
            row_coord,
            store
        );
    }
}

Coord get_selector_coord(
    int selected_row,
    int line_height,
    Grid_Cell& grid_cell,
    Coord& coord
) {
    if (selected_row < grid_cell.fields.size()) {
        return {
            coord.x - line_height,
            coord.y + line_height + (line_height * selected_row)
        };
    } else {
        return {
            coord.x - line_height,
            coord.y + (line_height * 2) + (line_height * selected_row)
        };
    }
}

bool should_show_underline(
    Event_Field& field,
    int index,
    Event_Editor& ee
) {
    return (
        (field.key == "delay" || field.key == "cond" || field.key == "mod")
        && ee.selected_row == index
    );
}

void underline_elt(
    Value_Display_Res value_display_res,
    Event_Field& field,
    Coord& coord,
    Store& store
) {
    auto& idxs = value_display_res.underline_idxs[store.event_editor.selected_col];

    for (int i = idxs.first; i < idxs.second; ++i) {
        int begin = (field.key + ": ").size() + i;
        Coord underline_coord = {
            coord.x + (begin * store.font_width),
            coord.y + 14
        };

        image_elt(store.images["select-underline"], underline_coord, store);
    }
}
