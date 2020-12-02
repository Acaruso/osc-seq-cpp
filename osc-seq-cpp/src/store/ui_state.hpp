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
    bool i1;
    bool i2;
    bool i3;
    bool i4;
    bool i5;
    bool i6;

    bool keydown_event;

    Mode mode;

    Ui_State();
};
