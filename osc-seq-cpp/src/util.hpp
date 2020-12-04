#pragma once

#include "store/coord.hpp"
#include "store/rect.hpp"
#include "store/ui_state.hpp"

enum class Event { Space, Tab, Mouseup, Mousedown, w, a, s, d };

bool is_clicked(Rect& rect, Ui_State& ui_state);

bool is_mousedown_event_inside_rect(
    Rect& rect,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
);

bool is_mouseup_event_inside_rect(
    Rect& rect,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
);

bool is_event(Event event, Ui_State& ui_state, Ui_State& prev_ui_state);

bool is_coord_inside_rect(int x, int y, Rect rect);

bool is_coord_inside_rect(Coord coord, Rect rect);

int clamp(int x, int min, int max);

void increment(int& x, int min, int max);

void decrement(int& x, int min, int max);
