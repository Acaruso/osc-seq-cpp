#include "input_system.hpp"

#include <iostream>

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
		case SDL_MOUSEMOTION:
			mouse_motion(event, ui_state);
			break;
		case SDL_KEYDOWN:
			keydown(event, ui_state);
			break;
		case SDL_KEYUP:
			keyup(event, ui_state);
			break;
		}
	}

    if (ui_state.click) {
        ui_state.prev_drag_x = ui_state.drag_x;
        ui_state.prev_drag_y = ui_state.drag_y;
        ui_state.drag_x = ui_state.x;
        ui_state.drag_y = ui_state.y;
    }
}

void mouse_button_down(SDL_Event& event, Ui_State& ui_state) {
    ui_state.mousedown_event = true;
	ui_state.click = true;
    ui_state.drag_x = ui_state.x;
    ui_state.drag_y = ui_state.y;
}

void mouse_button_up(SDL_Event& event, Ui_State& ui_state) {
    ui_state.mouseup_event = true;
	ui_state.click = false;
    ui_state.cur_elt_id = "";
}

void mouse_motion(SDL_Event& event, Ui_State& ui_state) {
    ui_state.x = event.motion.x;
    ui_state.y = event.motion.y;
}

void keydown(SDL_Event& event, Ui_State& ui_state) {
    ui_state.keydown_event = true;

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
	case SDLK_SPACE:
		ui_state.space = true;
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
	case SDLK_SPACE:
		ui_state.space = false;
		break;
	}
}
