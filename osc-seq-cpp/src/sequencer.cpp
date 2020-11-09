#include "sequencer.hpp"
#include "systems/input_system.hpp"
#include "systems/control_system.hpp"
#include "systems/update_system.hpp"
#include "systems/draw_system.hpp"
#include "sdl/sdl_wrapper.hpp"

void loop(Store& store) {
    std::string path = "image\\smiley.png";

    auto texture = load_image(path, store.window_renderer);
    int t_w;
    int t_h;
    SDL_QueryTexture(texture, NULL, NULL, &t_w, &t_h);
    SDL_Rect rect = { 100, 100, t_w / 3, t_h / 3 };

	while (!store.ui_state.quit) {
		clear_window(store.window_renderer);

        SDL_RenderCopy(store.window_renderer, texture, NULL, &rect);

        input_system(store.ui_state);

        control_system(store);

        update_system(store);

        draw_system(store);

        // unset click
		store.ui_state.click = false;

		SDL_Delay(10);
	}
}
