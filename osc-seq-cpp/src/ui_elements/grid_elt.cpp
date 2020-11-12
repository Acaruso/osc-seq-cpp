#include "grid_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"
#include "rect_elt.hpp"
#include "image_elt.hpp"

void grid_elt(
    Coord coord,
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    for (int i = 0; i < grid.numRows; i++) {
        for (int k = 0; k < grid.numCols; k++) {
            Grid_Cell& grid_cell = grid.data[i][k];

            Rect rect(
                grid.rect_w,
                grid.rect_h,
                (grid.rect_w * k) + coord.x,
                (grid.rect_h * i) + coord.y,
                grid_cell.toggled
            );

            rect_elt(
                rect,
                ui_state,
                window_renderer,
                []() {}
            );
        }
    }
}

void grid_elt_clickable(
    Coord coord,
    Grid& grid,
    Store& store,
    std::function<void()> on_click
) {
    auto fn = [&](Grid_Cell& grid_cell, int row, int col) {
        Rect rect(
            grid.rect_w,
            grid.rect_h,
            (grid.rect_w * col) + coord.x,
            (grid.rect_h * row) + coord.y,
            grid_cell.toggled
        );

        Image_Set& image_set = get_image_set(col, store.images);

        Coord image_coord = { rect.x, rect.y };
        image_toggle_elt(
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
