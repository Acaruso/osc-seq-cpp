#include "sequencer.hpp"
#include "store/ui_state.hpp"
#include "store/grid.hpp"
#include "rect.hpp"
#include "util.hpp"

void loop(Store* store) {
	while (!store->ui_state.quit) {
		clear_window(store->window_renderer);

		handle_input_events(store->ui_state);

        do_rect(store->rect, store->ui_state, store->window_renderer);
        do_grid(store->grid, store->ui_state, store->window_renderer);

		// render backbuffer
		SDL_RenderPresent(store->window_renderer);

        // unset click
		store->ui_state.click = false;

		// sleep
		SDL_Delay(10);
	}
}

void do_grid(Grid& grid, Ui_State& ui_state, SDL_Renderer* window_renderer) {
    int grid_width = 20;
    int grid_height = 20;
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

            if (ui_state.click) {
                if (is_coord_inside_rect(ui_state.x, ui_state.y, rect)) {
                    grid.data[i][k].toggled = !grid.data[i][k].toggled;
                }
            }

            draw_rect(
                window_renderer,
                rect,
                grid.data[i][k].toggled
            );
        }
    }
}

void do_rect(Rect& rect, Ui_State& ui_state, SDL_Renderer* window_renderer) {
    int movement_amount = 3;

    // if (store->ui_state.click) {
    // 	store->rect.x = store->ui_state.x;
    // 	store->rect.y = store->ui_state.y;
    // }

    if (ui_state.up) {
        rect.y -= movement_amount;
    }
    else if (ui_state.down) {
        rect.y += movement_amount;
    }
    else if (ui_state.right) {
        rect.x += movement_amount;
    }
    else if (ui_state.left) {
        rect.x -= movement_amount;
    }

    draw_rect(window_renderer, rect, true);
}
