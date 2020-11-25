#include "ui_state.hpp"

Ui_State::Ui_State()
{
	click = false;
	x = 0;
	y = 0;

    drag_x = 0;
    drag_y = 0;
    prev_drag_x = 0;
    prev_drag_y = 0;

    cur_elt_id = "";

	up = false;
	down = false;
	left = false;
	right = false;
    w = false;
    a = false;
    s = false;
    d = false;
    space = false;
    lshift = false;
    tab = false;
	quit = false;

    keydown_event = false;

    mode = Normal;
}
