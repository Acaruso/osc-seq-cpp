#pragma once
#include <SDL.h>

struct Ui_State {
	bool quit;
	bool click;
	int x;
	int y;
	bool up;
	bool down;
	bool right;
	bool left;

    Ui_State();
};

void handle_input_events(Ui_State& ui_state);
void mouse_button_down(SDL_Event& event, Ui_State& ui_state);
void keydown(SDL_Event& event, Ui_State& ui_state);
void keyup(SDL_Event& event, Ui_State& ui_state);
