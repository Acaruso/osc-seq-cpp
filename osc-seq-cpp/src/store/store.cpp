#include "store.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"

Store::Store() {
	Init_Sdl_Res init_sdl_res = init_sdl();

	window = init_sdl_res.window;
	window_surface = init_sdl_res.window_surface;
	window_renderer = init_sdl_res.window_renderer;

    rect.h = 10;
    rect.w = 10;
    rect.x = 10;
    rect.y = 10;

    seq_grid = Seq_Grid(2, 4, 40, 40);

    bpm = 120;
    clock = 0;
    time_divisions = get_time_divisions(bpm);

    images["arrow-down"] = load_image("image/arrow-down.png", window_renderer);
    images["arrow-up"] = load_image("image/arrow-up.png", window_renderer);

    fonts["dos"] = TTF_OpenFont("image/Perfect-DOS-VGA-437.ttf", 16);
}
