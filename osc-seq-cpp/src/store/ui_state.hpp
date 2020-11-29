#pragma once

#include <functional>
#include <string>

#include <SDL.h>

enum Mode
{
    Normal,
    Target_Select
};

struct Ui_State
{
	bool click;
	int x;
	int y;

    int drag_x;
    int drag_y;
    int prev_drag_x;
    int prev_drag_y;

    std::string cur_elt_id;

	bool up;
	bool down;
	bool right;
	bool left;
    bool w;
    bool a;
    bool s;
    bool d;
    bool space;
    bool lshift;
    bool tab;
	bool quit;

    bool keydown_event;

    Mode mode;

    Ui_State();
};
