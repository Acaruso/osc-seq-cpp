#include "grid_elt.hpp"

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"
#include "rect_elt.hpp"

void grid_elt(
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
                (grid.rect_w * k) + grid.x,
                (grid.rect_h * i) + grid.y,
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
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    auto fn = [&](Grid_Cell& grid_cell, int row, int col) {
        Rect rect(
            grid.rect_w,
            grid.rect_h,
            (grid.rect_w * col) + grid.x,
            (grid.rect_h * row) + grid.y,
            grid_cell.toggled
        );

        auto rect_on_click = [&]() {
            grid_cell.toggled = !grid_cell.toggled;
        };

        rect_elt(
            rect,
            ui_state,
            window_renderer,
            rect_on_click
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
