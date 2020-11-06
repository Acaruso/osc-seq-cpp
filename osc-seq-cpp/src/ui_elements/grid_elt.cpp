#include "grid_elt.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"
#include "../sdl/sdl_wrapper.hpp"
#include "rect_elt.hpp"

int rect_w = 40;
int rect_h = 40;

void do_grid(
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    for (int i = 0; i < grid.numRows; i++) {
        for (int k = 0; k < grid.numCols; k++) {
            Grid_Cell& grid_cell = grid.data[i][k];

            Rect rect(
                rect_w,
                rect_h,
                (rect_w * k) + grid.x,
                (rect_h * i) + grid.y,
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
        }
    }
}

void draw_grid(Grid& grid, SDL_Renderer* window_renderer) {

}
