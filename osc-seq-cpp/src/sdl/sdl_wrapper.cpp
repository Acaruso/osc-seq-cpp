#include "sdl_wrapper.hpp"

Init_sdl_res* init_sdl() {
	Init_sdl_res* res = new Init_sdl_res;

	SDL_Init(SDL_INIT_VIDEO);

	res->window = SDL_CreateWindow(
		"title",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	res->window_surface = SDL_GetWindowSurface(res->window);
	res->window_renderer = SDL_CreateRenderer(res->window, -1, SDL_RENDERER_ACCELERATED);

	return res;
}

void clear_window(SDL_Renderer* window_renderer) {
	SDL_SetRenderDrawColor(window_renderer, 255, 255, 255, 255);
	SDL_RenderClear(window_renderer);
}

void draw_rect(SDL_Renderer* window_renderer, Rect rect, bool fill) {
    SDL_Rect sdl_rect;
    sdl_rect.w = rect.w;
    sdl_rect.h = rect.h;
    sdl_rect.x = rect.x;
    sdl_rect.y = rect.y;

    if (fill) {
        SDL_RenderFillRect(window_renderer, &sdl_rect);
    } else {
        SDL_RenderDrawRect(window_renderer, &sdl_rect);
    }
}
