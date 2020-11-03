#include "sequencer.hpp"

void keydown(SDL_Event& event, Ui_State& ui_state);
void keyup(SDL_Event& event, Ui_State& ui_state);

void loop(Store* store) {
	SDL_Event event;
	bool quit = false;
	while (!store->ui_state.quit) {
		// clear window

		SDL_SetRenderDrawColor(store->window_renderer, 255, 255, 255, 255);
		SDL_RenderClear(store->window_renderer);

		// handle input events

		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				printf("quit");
				store->ui_state.quit = true;
				break;
			case SDL_KEYDOWN:
				keydown(event, store->ui_state);
				break;
			case SDL_KEYUP:
				keyup(event, store->ui_state);
				break;
			}
		}

		// move rectangle

		int movement_amount = 3;

		if (store->ui_state.up) {
			store->rect.y -= movement_amount;
		}
		else if (store->ui_state.down) {
			store->rect.y += movement_amount;
		}
		else if (store->ui_state.right) {
			store->rect.x += movement_amount;
		}
		else if (store->ui_state.left) {
			store->rect.x -= movement_amount;
		}

		// draw stuff to backbuffer

		SDL_SetRenderDrawColor(store->window_renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(store->window_renderer, &store->rect);

		// render backbuffer

		SDL_RenderPresent(store->window_renderer);

		// sleep

		SDL_Delay(10);
	}
}

void keydown(SDL_Event& event, Ui_State& ui_state) {
	switch (event.key.keysym.sym) {
	case SDLK_UP:
		ui_state.up = true;
		break;
	case SDLK_DOWN:
		ui_state.down = true;
		break;
	case SDLK_LEFT:
		ui_state.left = true;
		break;
	case SDLK_RIGHT:
		ui_state.right = true;
		break;
	}
}

void keyup(SDL_Event& event, Ui_State& ui_state) {
	switch (event.key.keysym.sym) {
	case SDLK_UP:
		ui_state.up = false;
		break;
	case SDLK_DOWN:
		ui_state.down = false;
		break;
	case SDLK_LEFT:
		ui_state.left = false;
		break;
	case SDLK_RIGHT:
		ui_state.right = false;
		break;
	}
}