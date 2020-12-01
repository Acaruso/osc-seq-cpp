#include "grid_elt.hpp"

#include <iostream>

#include "../../sdl/sdl_wrapper.hpp"
#include "../../store/rect.hpp"
#include "../../util.hpp"
#include "../image_elt.hpp"
#include "grid_cell_elt.hpp"

void grid_elt(
    Coord coord,
    int padding,
    Event_Grid& grid,
    Store& store,
    std::function<void()> on_click
) {
    grid.for_each([&](Grid_Cell& grid_cell, int row, int col) {
        Coord image_coord = {
            ((grid.rect_w + padding * 2) * col) + coord.x + padding,
            ((grid.rect_h + padding * 2) * row) + coord.y + padding
        };

        image_elt_toggleable(
            store.images["button-small"],
            grid_cell.toggled,
            image_coord,
            store
        );
    });
}

void grid_elt_clickable(
    Coord coord,
    int padding,
    Event_Grid& grid,
    Seq_Grid& seq_grid,
    Store& store,
    std::function<void()> on_click
) {
    grid_select_elt(
        coord,
        padding,
        grid,
        seq_grid,
        store
    );

    grid.for_each([&](Grid_Cell& grid_cell, int row, int col) {
        Image_Set& image_set = get_image_set(col, store.images);

        Coord cell_coord = {
            ((grid.rect_w + padding * 2) * col) + coord.x + padding,
            ((grid.rect_h + padding * 2) * row) + coord.y + padding
        };

        auto on_grid_cell_click = [&]() {
            seq_grid.set_toggled(row, col, store.ui_state, store.event_editor);
        };

        grid_cell_elt(
            image_set,
            grid_cell.toggled,
            cell_coord,
            store,
            on_grid_cell_click
        );

        if (col == grid.numCols - 1) {
            Coord mute_coord = {
                (grid.rect_w + padding * 2) + cell_coord.x,
                cell_coord.y + 5
            };
            auto& row_metadata = seq_grid.get_row_metadata(row);
            image_elt_clickable_toggleable(
                store.images["button-mute"],
                row_metadata.mute,
                mute_coord,
                store,
                [&]() { row_metadata.mute = !row_metadata.mute; }
            );
        }
    });
}

void grid_select_elt(
    Coord coord,
    int padding,
    Event_Grid& grid,
    Seq_Grid& seq_grid,
    Store& store
) {
    Coord selection_coord = {
        ((grid.rect_w + padding * 2) * seq_grid.selected_col) + coord.x,
        ((grid.rect_h + padding * 2) * seq_grid.selected_row) + coord.y
    };
    image_elt(
        store.images["button-selection"],
        selection_coord,
        store
    );

    if (store.ui_state.mode == Target_Select) {
        Coord selection_coord = {
            ((grid.rect_w + padding * 2) * seq_grid.selected_target_col) + coord.x,
            ((grid.rect_h + padding * 2) * seq_grid.selected_target_row) + coord.y
        };
        image_elt_blink(
            store.images["button-selection-green"],
            selection_coord,
            store
        );
    }
}

Image_Set& get_image_set(int col, std::unordered_map<std::string, Image_Set>& images)
{
    if (col / 4 == 0) {
        return images["button-green"];
    } else if (col / 4 == 1) {
        return images["button-orange"];
    } else if (col / 4 == 2) {
        return images["button-pink"];
    } else if (col / 4 == 3) {
        return images["button-red"];
    }
}
