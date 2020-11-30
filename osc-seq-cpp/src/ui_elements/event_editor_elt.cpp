#include "event_editor_elt.hpp"

#include <iostream>
#include <string>

#include "image_elt.hpp"
#include "text_elt.hpp"

void event_editor_wrapper_elt(
    Coord& coord,
    Store& store
) {
    Grid_Cell& grid_cell = store.seq_grid.get_selected_cell();

    event_editor_selector(grid_cell, coord, store);

    event_editor_elt(
        "Event Editor",
        grid_cell,
        false,
        coord,
        store
    );

    Coord meta_coord = {
        coord.x,
        coord.y + store.line_height + (grid_cell.fields.size() * store.line_height)
    };

    event_editor_elt(
        "Meta Event Editor",
        grid_cell,
        true,
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
    Grid_Cell& grid_cell,
    bool is_meta,
    Coord& coord,
    Store& store
) {
    text_elt(header, coord, store);

    auto& fields = is_meta ? grid_cell.meta_fields : grid_cell.fields;

    int i = 0;

    for (auto& field : fields) {
        event_editor_row_elt(field, grid_cell, is_meta, coord, i++, store);
    }
}

void event_editor_row_elt(
    Event_Field& field,
    Grid_Cell& grid_cell,
    bool is_meta,
    Coord& coord,
    int index,
    Store& store
) {
    std::string text = field.get_display_str(grid_cell.toggled);

    Coord row_coord = {
        coord.x,
        coord.y + store.line_height + (index * store.line_height)
    };

    text_elt(text, row_coord, store);

    if (should_show_underline(field, grid_cell, is_meta, index, store.event_editor)) {
        underline_elt(text, field, row_coord, store);
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
    Grid_Cell& grid_cell,
    bool is_meta,
    int index,
    Event_Editor& ee
) {
    if (
        grid_cell.toggled
        && !is_meta
        && field.key == "delay"
        && ee.selected_row == index
    ) {
        return true;
    } else {
        return false;
    }
}

void underline_elt(
    std::string text,
    Event_Field& field,
    Coord& coord,
    Store& store
) {
    Coord underline_coord;

    if (field.key == "delay") {
        underline_coord = get_delay_underline_coord(
            text,
            coord,
            store.font_width,
            store.event_editor
        );
    } else if (field.key == "target") {
        underline_coord = get_target_underline_coord(
            text,
            coord,
            store.font_width,
            store.event_editor
        );
    }

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

Coord get_target_underline_coord(
    std::string text,
    Coord row_coord,
    int font_width,
    Event_Editor& event_editor
) {
    int begin = 0;
    if (event_editor.selected_col == 0) {
        begin = text.find(":") + 3;
    } else if (event_editor.selected_col == 1) {
        begin = text.find(",") + 2;
    }

    return {
        row_coord.x + (begin * font_width),
        row_coord.y + 14
    };
}
