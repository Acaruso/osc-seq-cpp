#include "grid_elt.hpp"
#include "rect.hpp"
#include "../util.hpp"
#include "../sdl/sdl_wrapper.hpp"

void do_grid(Grid& grid, Ui_State& ui_state, SDL_Renderer* window_renderer) {
    int grid_width = 40;
    int grid_height = 40;
    int grid_x = 100;
    int grid_y = 100;

    for (int i = 0; i < grid.data.size(); i++) {
        auto row = grid.data[i];
        for (int k = 0; k < row.size(); k++) {
            Rect rect(
                grid_width,
                grid_height,
                (grid_width * k) + grid_x,
                (grid_height * i) + grid_y
            );

            if (is_clicked(rect, ui_state)) {
                grid.data[i][k].toggled = !grid.data[i][k].toggled;
            }

            draw_rect(
                window_renderer,
                rect,
                grid.data[i][k].toggled
            );
        }
    }
}
