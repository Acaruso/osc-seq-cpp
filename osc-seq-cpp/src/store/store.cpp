#include "store.hpp"
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

    grid = Grid(2, 4);

    bpm = 120;
    clock = 0;
}
