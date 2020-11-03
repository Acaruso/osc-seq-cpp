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
};

struct Store {
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
	Ui_State ui_state;
	SDL_Rect rect;
};

Store* init_store();
