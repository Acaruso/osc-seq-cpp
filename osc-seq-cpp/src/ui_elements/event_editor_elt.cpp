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

    if (grid_cell.has_meta) {
        Coord meta_coord {
            coord.x,
            coord.y + ((grid_cell.data.size() + 1) * store.line_height)
        };
        meta_event_editor_elt(grid_cell, meta_coord, store);
    }
}

void event_editor_selector(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    Coord select_coord = get_selector_coord(
        store.event_editor.selected_row,
        grid_cell,
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

    for (auto& row : grid_cell.data) {
        event_editor_row_elt(row, grid_cell.toggled, coord, i++, store);
    }
}

void meta_event_editor_elt(
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store
) {
    text_elt("Meta Event Editor", coord, store);

    int i = 0;

    for (auto& row : grid_cell.meta_data) {
        event_editor_row_elt(row, grid_cell.toggled, coord, i++, store);
    }
}

void event_editor_row_elt(
    Grid_Cell_Data& grid_cell_data,
    bool toggled,
    Coord& coord,
    int index,
    Store& store
) {
    std::string key = grid_cell_data.key;
    std::string value = grid_cell_data.get_value_str();

    if (!toggled) {
        value = "";
    }

    Coord row_coord = { coord.x, (coord.y + store.line_height) + (index * store.line_height) };

    std::string text = key + ": " + value;

    text_elt(text, row_coord, store);

    if (
        toggled
        && (grid_cell_data.options & Op_Delay)
        && store.event_editor.selected_row == index
    ) {
        Coord underline_coord = get_delay_underline_coord(
            text,
            row_coord,
            store.font_width
        );

        image_elt(store.images["select-underline"], underline_coord, store);
    }
}

Coord get_selector_coord(int selected_row, Grid_Cell& grid_cell, int line_height, Coord& coord)
{
    // data
    if (selected_row < grid_cell.data.size()) {
        return {
            coord.x - line_height,
            coord.y + line_height + (line_height * selected_row)
        };
    // meta data
    } else {
        return {
            coord.x - line_height,
            coord.y + (line_height * 2) + (line_height * selected_row)
        };
    }
}

Coord get_delay_underline_coord(std::string text, Coord row_coord, int font_width)
{
    int begin = text.find(": ") + 2;
    return {
        row_coord.x + (begin * font_width),
        row_coord.y + 14
    };
}
