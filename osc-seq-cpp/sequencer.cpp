#include "sequencer.hpp"
#include "app_db.hpp"

void rect_system(Store* store);
void handle_input_events(Ui_State& ui_state);
void mouse_button_down(SDL_Event& event, Ui_State& ui_state);
void keydown(SDL_Event& event, Ui_State& ui_state);
void keyup(SDL_Event& event, Ui_State& ui_state);

void loop(Store* store) {
	while (!store->ui_state.quit) {
		clear_window(store->window_renderer);

		handle_input_events(store->ui_state);

		rect_system(store);

		// move rectangle

		int movement_amount = 3;

		//if (store->ui_state.click) {
		//	store->rect.x = store->ui_state.x;
		//	store->rect.y = store->ui_state.y;
		//}

		//if (store->ui_state.up) {
		//	store->rect.y -= movement_amount;
		//}
		//else if (store->ui_state.down) {
		//	store->rect.y += movement_amount;
		//}
		//else if (store->ui_state.right) {
		//	store->rect.x += movement_amount;
		//}
		//else if (store->ui_state.left) {
		//	store->rect.x -= movement_amount;
		//}

		// unset click

		store->ui_state.click = false;

		// draw stuff to backbuffer

		//SDL_SetRenderDrawColor(store->window_renderer, 0, 0, 0, 255);
		//SDL_RenderDrawRect(store->window_renderer, &store->rect);

		// render backbuffer

		SDL_RenderPresent(store->window_renderer);

		// sleep

		SDL_Delay(10);
	}
}

void rect_system(Store* store) {
	std::vector<PositionRect> rects = store->app_db->getPositionRects();

	for (auto rect : rects) {
		SDL_SetRenderDrawColor(store->window_renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(store->window_renderer, &store->rect);
	}
}

void handle_input_events(Ui_State& ui_state) {
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			ui_state.quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse_button_down(event, ui_state);
			break;
		case SDL_KEYDOWN:
			keydown(event, ui_state);
			break;
		case SDL_KEYUP:
			keyup(event, ui_state);
			break;
		}
	}
}

void mouse_button_down(SDL_Event& event, Ui_State& ui_state) {
	ui_state.click = true;
	ui_state.x = event.motion.x;
	ui_state.y = event.motion.y;
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