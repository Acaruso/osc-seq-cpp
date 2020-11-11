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

    Image_Set arrow_up;
    arrow_up.image = load_image("image/arrow-up.png", window_renderer);
    arrow_up.image_hot = load_image("image/arrow-up-hot.png", window_renderer);
    arrow_up.image_active = load_image("image/arrow-up-active.png", window_renderer);

    Image_Set arrow_down;
    arrow_down.image = load_image("image/arrow-down.png", window_renderer);
    arrow_down.image_hot = load_image("image/arrow-down-hot.png", window_renderer);
    arrow_down.image_active = load_image("image/arrow-down-active.png", window_renderer);

    Image_Set button;
    arrow_down.image = load_image("image/button.png", window_renderer);
    arrow_down.image_hot = load_image("image/button-hot.png", window_renderer);
    arrow_down.image_active = load_image("image/button-active.png", window_renderer);

    images["arrow-up"] = arrow_up;
    images["arrow-down"] = arrow_down;
    images["button"] = button;

    fonts["dos"] = TTF_OpenFont("image/Perfect-DOS-VGA-437.ttf", 16);
}
