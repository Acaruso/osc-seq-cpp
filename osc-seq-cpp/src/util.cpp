#include "util.hpp"

bool is_clicked(Rect& rect, Ui_State& ui_state) {
    return (ui_state.click && is_coord_inside_rect(ui_state.x, ui_state.y, rect));
}

bool is_mousedown_inside_rect(Rect& rect, Ui_State& ui_state) {
    return (ui_state.mousedown_event && is_coord_inside_rect(ui_state.x, ui_state.y, rect));
}

bool is_mouseup_inside_rect(Rect& rect, Ui_State& ui_state) {
    return (ui_state.mouseup_event && is_coord_inside_rect(ui_state.x, ui_state.y, rect));
}

bool is_coord_inside_rect(int x, int y, Rect rect) {
    return (
        x >= rect.x &&
        y >= rect.y &&
        x <= rect.x + rect.w &&
        y <= rect.y + rect.h
    );
}

bool is_coord_inside_rect(Coord coord, Rect rect) {
    return (
        coord.x >= rect.x &&
        coord.y >= rect.y &&
        coord.x <= rect.x + rect.w &&
        coord.y <= rect.y + rect.h
    );
}
