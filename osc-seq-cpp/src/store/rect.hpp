#pragma once

struct Rect {
    int w;
    int h;
    int x;
    int y;
    bool toggled;
    Rect();
    Rect(int w, int h, int x, int y);
    Rect(int w, int h, int x, int y, bool toggled);
};
