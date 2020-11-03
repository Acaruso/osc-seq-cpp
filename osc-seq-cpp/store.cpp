#include "store.hpp"
#include "sdl_wrapper.hpp"

Store* init_store() {
	Store* store = new Store;

	Init_sdl_res* init_sdl_res = init_sdl();

	store->window = init_sdl_res->window;
	store->window_surface = init_sdl_res->window_surface;
	store->window_renderer = init_sdl_res->window_renderer;

	delete init_sdl_res;

	return store;
}