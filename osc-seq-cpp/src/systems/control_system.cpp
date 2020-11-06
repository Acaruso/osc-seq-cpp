#include "control_system.hpp"

void control_system(Store& store) {
    control_rect_system(store.rect, store.ui_state);
}

void control_rect_system(Rect& rect, Ui_State& ui_state) {
    int movement_amount = 3;

    // if (store.ui_state.click) {
    // 	store.rect.x = store.ui_state.x;
    // 	store.rect.y = store.ui_state.y;
    // }

    if (ui_state.up) {
        rect.y -= movement_amount;
    }
    if (ui_state.down) {
        rect.y += movement_amount;
    }
    if (ui_state.right) {
        rect.x += movement_amount;
    }
    if (ui_state.left) {
        rect.x -= movement_amount;
    }
}
