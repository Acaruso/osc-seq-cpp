#include "util.hpp"

bool is_coord_inside_rect(int x, int y, Rect rect) {
    return (
        x >= rect.x &&
        y >= rect.y &&
        x <= rect.x + rect.w &&
        y <= rect.y + rect.h
    );
}
