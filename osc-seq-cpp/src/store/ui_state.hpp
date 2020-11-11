#pragma once

#include <functional>
#include <string>

#include <SDL.h>

struct Ui_State {
	bool click;
    bool mousedown_event;
    bool mouseup_event;
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
	bool quit;

    std::function<void(int drag_distance)> on_drag;

    Ui_State();
};
