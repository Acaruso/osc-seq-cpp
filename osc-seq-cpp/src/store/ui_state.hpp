#pragma once

#include <functional>
#include <string>

#include <SDL.h>

enum Mode
{
    Normal,
    Target_Select,
    Pattern_Copy,
    Dropdown
};

struct Ui_State
{
	bool click{false};
	int cx{0};
	int cy{0};

    int drag_x{0};
    int drag_y{0};
    int prev_drag_x{0};
    int prev_drag_y{0};

    std::string cur_elt_id{""};

	bool up{false};
	bool down{false};
	bool right{false};
	bool left{false};
    bool w{false};
    bool a{false};
    bool s{false};
    bool d{false};
    bool e{false};
    bool q{false};
    bool c{false};
    bool v{false};
    bool r{false};
    bool p{false};
    bool x{false};
    bool f{false};
    bool space{false};
    bool lshift{false};
    bool lctrl{false};
    bool lalt{false};
    bool tab{false};
	bool quit{false};
    bool i1{false};
    bool i2{false};
    bool i3{false};
    bool i4{false};
    bool i5{false};
    bool i6{false};
    bool esc{false};

    bool keydown_event{false};

    Mode mode{Normal};
};
