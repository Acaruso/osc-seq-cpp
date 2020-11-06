#include "rect.hpp"

Rect::Rect() {}

Rect::Rect(int w, int h, int x, int y)
    : w(w), h(h), x(x), y(y), toggled(false) {
}

Rect::Rect(int w, int h, int x, int y, bool toggled)
    : w(w), h(h), x(x), y(y), toggled(toggled) {
}
