#include "ui_state.hpp"

Ui_State::Ui_State() {
	click = false;
    mousedown_event = false;
    mouseup_event = false;
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
	quit = false;

    timer = 0;
    keydown_event = false;
}
