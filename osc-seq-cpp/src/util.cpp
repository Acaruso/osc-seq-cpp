#include "util.hpp"

bool is_clicked(Rect& rect, Ui_State& ui_state) {
    return (ui_state.click && is_coord_inside_rect(ui_state.x, ui_state.y, rect));
}

bool is_coord_inside_rect(int x, int y, Rect rect) {
    return (
        x >= rect.x &&
        y >= rect.y &&
        x <= rect.x + rect.w &&
        y <= rect.y + rect.h
    );
}
