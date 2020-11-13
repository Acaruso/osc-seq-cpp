#pragma once

#include "../store/rect.hpp"
#include "../store/store.hpp"
#include "../store/ui_state.hpp"

void control_system(Store& store);

void control_rect_system(Rect& rect, Ui_State& ui_state);

void control_grid_selection_system(
    int& selection_row,
    int& selection_col,
    Ui_State& ui_state
);
