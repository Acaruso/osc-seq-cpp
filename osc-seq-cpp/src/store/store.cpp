#include "store.hpp"
#include "../sdl/sdl_wrapper.hpp"

Time_Divisions init_time_divisions(int bpm) {
    Time_Divisions td;

    td.n4 = 6000 / bpm;
    td.n8 = td.n4 / 2;
    td.n16 = td.n4 / 4;
    td.n2 = td.n4 * 2;
    td.n1 = td.n4 * 4;

    td.n12 = td.n4 / 3;
    td.n6 = td.n12 * 2;
    td.n3 = td.n6 * 2;

    return td;
}

Store::Store() {
	Init_Sdl_Res init_sdl_res = init_sdl();

	window = init_sdl_res.window;
	window_surface = init_sdl_res.window_surface;
	window_renderer = init_sdl_res.window_renderer;

    rect.h = 10;
    rect.w = 10;
    rect.x = 10;
    rect.y = 10;

    grid = Grid(30, 30, 2, 4, 30, 30);
    grid2 = Grid(200, 200, 2, 4, 30, 20);

    seq_grid = Seq_Grid(30, 30, 2, 4, 40, 40);

    bpm = 820;
    clock = 0;
    time_divisions = init_time_divisions(bpm);
}
