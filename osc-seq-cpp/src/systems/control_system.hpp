#pragma once
#include "../store/store.hpp"
#include "../store/ui_state.hpp"
#include "../ui_elements/rect.hpp"

void control_system(Store& store);

void control_rect_system(Rect& rect, Ui_State& ui_state);
