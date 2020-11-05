#include "grid_elt.hpp"
#include "rect.hpp"
#include "../util.hpp"
#include "../sdl/sdl_wrapper.hpp"

struct Grid_Display_Options {
    int grid_width;
    int grid_height;
    int grid_x;
    int grid_y;
};

Grid_Display_Options grid_display_options = { 40, 40, 100, 100 };

void do_grid(
    Grid& grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    on_click();

    int grid_width = 40;
    int grid_height = 40;
    int grid_x = 100;
    int grid_y = 100;

    for (int i = 0; i < grid.data.size(); i++) {
        auto row = grid.data[i];
        for (int k = 0; k < row.size(); k++) {
            Grid_Cell& grid_cell = grid.data[i][k];

            Rect rect(
                grid_width,
                grid_height,
                (grid_width * k) + grid_x,
                (grid_height * i) + grid_y
            );

            if (is_clicked(rect, ui_state)) {
                grid_cell.toggled = !grid_cell.toggled;
            }

            draw_rect(
                window_renderer,
                rect,
                grid_cell.toggled
            );
        }
    }
}

void draw_grid(Grid& grid, SDL_Renderer* window_renderer) {

}
