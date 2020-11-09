#include "seq_grid_elt.hpp"

void seq_grid_elt(
    Seq_Grid& seq_grid,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    grid_elt(seq_grid.clock_grid, ui_state, window_renderer, on_click);
    grid_elt_clickable(seq_grid.clickable_grid, ui_state, window_renderer, on_click);
}
