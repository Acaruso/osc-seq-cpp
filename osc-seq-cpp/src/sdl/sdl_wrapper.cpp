#include "sdl_wrapper.hpp"

Init_Sdl_Res init_sdl() {
	Init_Sdl_Res res;

	SDL_Init(SDL_INIT_VIDEO);

	res.window = SDL_CreateWindow(
		"osc-seq",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	res.window_surface = SDL_GetWindowSurface(res.window);
	res.window_renderer = SDL_CreateRenderer(res.window, -1, SDL_RENDERER_ACCELERATED);

	return res;
}

void clear_window(SDL_Renderer* window_renderer) {
	SDL_SetRenderDrawColor(window_renderer, 255, 255, 255, 255);
	SDL_RenderClear(window_renderer);
}

void draw_rect(SDL_Renderer* window_renderer, Rect rect) {
    SDL_Rect sdl_rect;
    sdl_rect.w = rect.w;
    sdl_rect.h = rect.h;
    sdl_rect.x = rect.x;
    sdl_rect.y = rect.y;

    SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);

    if (rect.toggled) {
        SDL_RenderFillRect(window_renderer, &sdl_rect);
    } else {
        SDL_RenderDrawRect(window_renderer, &sdl_rect);
    }
}
