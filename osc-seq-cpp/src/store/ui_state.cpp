#include "ui_state.hpp"

Ui_State::Ui_State()
{
	click = false;
	cx = 0;
	cy = 0;

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
    e = false;
    q = false;
    c = false;
    v = false;
    r = false;
    p = false;
    x = false;
    f = false;
    space = false;
    lshift = false;
    lctrl = false;
    tab = false;
	quit = false;
    i1 = false;
    i2 = false;
    i3 = false;
    i4 = false;
    i5 = false;
    i6 = false;
    esc = false;

    keydown_event = false;

    mode = Normal;
}
