#include "grid_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"
#include "image_elt.hpp"
#include "grid_cell_elt.hpp"

void grid_elt(
    Coord coord,
    int padding,
    Grid& grid,
    Store& store,
    std::function<void()> on_click
) {
    auto fn = [&](Grid_Cell& grid_cell, int row, int col) {
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
    };

    grid_for_each(grid, fn);
}

void grid_elt_clickable(
    Coord coord,
    int padding,
    Grid& grid,
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

    auto fn = [&](Grid_Cell& grid_cell, int row, int col) {
        Image_Set& image_set = get_image_set(col, store.images);

        Coord image_coord = {
            ((grid.rect_w + padding * 2) * col) + coord.x + padding,
            ((grid.rect_h + padding * 2) * row) + coord.y + padding
        };

        auto on_grid_cell_click = [&]() {
            if (!store.ui_state.lshift) {
                grid_cell.toggled = !grid_cell.toggled;
            }
            seq_grid.selected_row = row;
            seq_grid.selected_col = col;
        };

        grid_cell_elt(
            image_set,
            grid_cell,
            image_coord,
            store,
            on_grid_cell_click
        );
    };

    grid_for_each(grid, fn);
}

void grid_for_each(Grid& grid, std::function<void(Grid_Cell&, int, int)> fn)
{
    for (int i = 0; i < grid.numRows; i++) {
        for (int k = 0; k < grid.numCols; k++) {
            Grid_Cell& grid_cell = grid.data[i][k];
            fn(grid_cell, i, k);
        }
    }
}

void grid_select_elt(
    Coord coord,
    int padding,
    Grid& grid,
    Seq_Grid& seq_grid,
    Store& store
) {
    Image_Set& image = store.ui_state.mode == Normal
        ? store.images["button-selection"]
        : store.images["button-selection-green"];

    Coord selection_coord = {
        ((grid.rect_w + padding * 2) * seq_grid.selected_col) + coord.x,
        ((grid.rect_h + padding * 2) * seq_grid.selected_row) + coord.y
    };

    image_elt(
        image,
        selection_coord,
        store
    );
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
