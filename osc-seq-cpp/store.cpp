#include "store.hpp"
#include "sdl_wrapper.hpp"

Store* init_store() {
	Store* store = new Store;

	Init_sdl_res* init_sdl_res = init_sdl();

	store->window = init_sdl_res->window;
	store->window_surface = init_sdl_res->window_surface;
	store->window_renderer = init_sdl_res->window_renderer;

	delete init_sdl_res;

	store->ui_state.up = false;
	store->ui_state.down = false;
	store->ui_state.left = false;
	store->ui_state.right = false;
	store->ui_state.quit = false;

	store->ui_state.click = false;
	store->ui_state.x = 0;
	store->ui_state.y = 0;

	store->rect.x = 20;
	store->rect.y = 20;
	store->rect.w = 20;
	store->rect.h = 20;

	return store;
}