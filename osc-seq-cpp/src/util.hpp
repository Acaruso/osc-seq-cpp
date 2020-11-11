#pragma once

#include "store/coord.hpp"
#include "store/rect.hpp"
#include "store/ui_state.hpp"

bool is_clicked(Rect& rect, Ui_State& ui_state);
bool is_mousedown(Rect& rect, Ui_State& ui_state);
bool is_mouseup(Rect& rect, Ui_State& ui_state);
bool is_coord_inside_rect(int x, int y, Rect rect);
bool is_coord_inside_rect(Coord coord, Rect rect);
