#include "sequencer.hpp"

void loop(Store* store) {
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		// clear window
		SDL_SetRenderDrawColor(store->window_renderer, 255, 255, 255, 255);
		SDL_RenderClear(store->window_renderer);

		// handle input events
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				printf("quit");
				quit = true;
				break;
			case SDL_KEYDOWN:
				printf("keydown");
				break;
			case SDL_KEYUP:
				printf("keyup");
				break;
			}
		}

		// draw stuff to backbuffer
		SDL_Rect r;
		r.x = 20;
		r.y = 20;
		r.w = 100;
		r.h = 100;

		SDL_SetRenderDrawColor(store->window_renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(store->window_renderer, &r);

		// render backbuffer
		SDL_RenderPresent(store->window_renderer);

		// sleep
		SDL_Delay(10);
	}
}
