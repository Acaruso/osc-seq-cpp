#include "input_system.hpp"

void input_system(Ui_State& ui_state) {
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			ui_state.quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse_button_down(event, ui_state);
			break;
		case SDL_MOUSEBUTTONUP:
			mouse_button_up(event, ui_state);
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

void mouse_button_up(SDL_Event& event, Ui_State& ui_state) {
	ui_state.click = false;
    ui_state.mouseup_event = true;
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
