#include "sdl_wrapper.hpp"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

Init_Sdl_Res init_sdl() {
	Init_Sdl_Res res;

	SDL_Init(SDL_INIT_EVERYTHING);

    IMG_Init(IMG_INIT_PNG);

    TTF_Init();

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

SDL_Texture* load_image(std::string path, SDL_Renderer* window_renderer) {
    SDL_Surface* buffer = IMG_Load(path.c_str());
    if (!buffer) {
        std::cout << "error loading image " << SDL_GetError() << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window_renderer, buffer);
    if (!texture) {
        std::cout << "error creating texture " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(buffer);
    return texture;
}

SDL_Rect rect_to_sdl_rect(Rect rect) {
    SDL_Rect sdl_rect;
    sdl_rect.w = rect.w;
    sdl_rect.h = rect.h;
    sdl_rect.x = rect.x;
    sdl_rect.y = rect.y;
    return sdl_rect;
}
