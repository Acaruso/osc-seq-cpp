#include "event_editor_elt.hpp"

#include <iostream>
#include <string>

#include "image_elt.hpp"
#include "text_elt.hpp"

void event_editor_wrapper_elt(
    Coord& coord,
    Store& store
) {
    Grid_Cell& grid_cell = store.seq_grid.get_selected();
    event_editor_selector(grid_cell, coord, store);
    event_editor_elt(grid_cell, coord, store);
}

void event_editor_selector(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    Coord select_coord = get_selector_coord(
        store.event_editor.selected_row,
        store.line_height,
        coord
    );

    image_elt(store.images["select-event-editor"], select_coord, store);
}

void event_editor_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    text_elt("Event Editor", coord, store);

    int i = 0;

    for (auto& field : grid_cell.fields) {
        event_editor_row_elt(field, grid_cell.toggled, coord, i++, store);
    }
}

void event_editor_row_elt(
    Event_Field& field,
    bool toggled,
    Coord& coord,
    int index,
    Store& store
) {
    std::string text = field.get_display_str(toggled);

    Coord row_coord = {
        coord.x,
        (coord.y + store.line_height) + (index * store.line_height)
    };

    text_elt(text, row_coord, store);

    if (
        toggled
        && field.key == "delay"
        && store.event_editor.selected_row == index
    ) {
        Coord underline_coord = get_delay_underline_coord(
            text,
            row_coord,
            store.font_width,
            store.event_editor
        );

        image_elt(store.images["select-underline"], underline_coord, store);
    }
}

Coord get_selector_coord(int selected_row, int line_height, Coord& coord)
{
    return {
        coord.x - line_height,
        coord.y + line_height + (line_height * selected_row)
    };
}

Coord get_delay_underline_coord(
    std::string text,
    Coord row_coord,
    int font_width,
    Event_Editor& event_editor
) {
    int begin = 0;
    if (event_editor.selected_col == 0) {
        begin = text.find(":") + 2;
    } else if (event_editor.selected_col == 1) {
        begin = text.find("/") + 2;
    }

    return {
        row_coord.x + (begin * font_width),
        row_coord.y + 14
    };
}
