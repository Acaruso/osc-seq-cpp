#include "pattern_grid_elt.hpp"

#include "../image_elt.hpp"

#include <iostream>

void pattern_grid_elt(
    Coord coord,
    int padding,
    Pattern_Grid& pattern_grid,
    Store& store,
    std::function<void()> on_click
) {
    auto& grid = pattern_grid.grid;

    grid.for_each([&](auto& grid_cell, int row, int col) {
        Image_Set& image_set = store.images["button-xs"];

        Coord image_coord = {
            ((grid.rect_w + padding * 2) * col) + coord.x + padding,
            ((grid.rect_h + padding * 2) * row) + coord.y + padding
        };

        auto on_grid_cell_click = [&]() {
            pattern_grid.set_selected(row, col);
            store.seq_grid.set_selected_pattern(pattern_grid);
        };

        image_elt_clickable_toggleable(
            image_set,
            grid_cell.toggled,
            image_coord,
            store,
            on_grid_cell_click
        );
    });
}
