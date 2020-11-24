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

    event_editor_elt(
        "Event Editor",
        grid_cell.fields,
        grid_cell.toggled,
        coord,
        store
    );

    Coord meta_coord = {
        coord.x,
        coord.y + store.line_height + (grid_cell.fields.size() * store.line_height)
    };

    event_editor_elt(
        "Meta Event Editor",
        grid_cell.meta_fields,
        grid_cell.toggled,
        meta_coord,
        store
    );
}

void event_editor_selector(
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
    std::vector<Event_Field> fields,
    bool toggled,
    Coord& coord,
    Store& store
) {
    text_elt(header, coord, store);

    int i = 0;

    for (auto& field : fields) {
        event_editor_row_elt(field, toggled, coord, i++, store);
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
        coord.y + store.line_height + (index * store.line_height)
    };

    text_elt(text, row_coord, store);

    if (should_show_underline(field, toggled, index, store.event_editor)) {
        underline_elt(text, row_coord, store);
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
    bool toggled,
    int index,
    Event_Editor& ee
) {
    return (toggled && field.key == "delay" && ee.selected_row == index);
}

void underline_elt(std::string text, Coord& coord, Store& store)
{
    Coord underline_coord = get_delay_underline_coord(
        text,
        coord,
        store.font_width,
        store.event_editor
    );

    image_elt(store.images["select-underline"], underline_coord, store);
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
