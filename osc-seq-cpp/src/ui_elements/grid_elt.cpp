#include "grid_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"
#include "rect_elt.hpp"
#include "image_elt.hpp"

void grid_elt(
    Coord coord,
    int padding,
    Grid& grid,
    Store& store,
    std::function<void()> on_click
) {
    // coord.x += padding;
    // coord.y += padding;

    auto fn = [&](Grid_Cell& grid_cell, int row, int col) {
        Coord image_coord = {
            ((grid.rect_w + padding * 2) * col) + coord.x + padding,
            ((grid.rect_h + padding * 2) * row) + coord.y + padding
        };

        // Coord image_coord = {
        //     ((grid.rect_w + padding) * col) + coord.x,
        //     ((grid.rect_h + padding) * row) + coord.y
        // };

        image_elt_toggleable(
            store.images["button-small"],
            grid_cell.toggled,
            image_coord,
            store.window_renderer
        );
    };

    grid_for_each(grid, fn);
}

void grid_elt_clickable(
    Coord coord,
    int padding,
    Grid& grid,
    Store& store,
    std::function<void()> on_click
) {
    Coord selection_coord = { coord.x, coord.y };
    image_elt(
        store.images["button-selection"],
        selection_coord,
        store.ui_state,
        store.window_renderer,
        []() {}
    );

    // coord.x += padding;
    // coord.y += padding * 2;

    // coord.y += padding;

    auto fn = [&](Grid_Cell& grid_cell, int row, int col) {
        Image_Set& image_set = get_image_set(col, store.images);

        Coord image_coord = {
            ((grid.rect_w + padding * 2) * col) + coord.x + padding,
            ((grid.rect_h + padding * 2) * row) + coord.y + padding
        };

        image_elt_clickable_toggleable(
            image_set,
            grid_cell.toggled,
            image_coord,
            store.ui_state,
            store.window_renderer,
            [&]() { grid_cell.toggled = !grid_cell.toggled; }
        );
    };

    grid_for_each(grid, fn);
}

void grid_for_each(Grid& grid, std::function<void(Grid_Cell&, int, int)> fn) {
    for (int i = 0; i < grid.numRows; i++) {
        for (int k = 0; k < grid.numCols; k++) {
            Grid_Cell& grid_cell = grid.data[i][k];
            fn(grid_cell, i, k);
        }
    }
}

Image_Set& get_image_set(int col, std::unordered_map<std::string, Image_Set>& images) {
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
