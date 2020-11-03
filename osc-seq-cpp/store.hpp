#pragma once
#include <SDL.h>

struct Ui_State {
	bool up;
	bool down;
	bool right;
	bool left;
	bool quit;
};

struct Store {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
	Ui_State ui_state;
	SDL_Rect rect;
};

Store* init_store();
