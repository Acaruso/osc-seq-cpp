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
