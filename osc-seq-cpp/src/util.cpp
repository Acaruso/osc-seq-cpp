#include "util.hpp"

bool is_clicked(Rect& rect, Ui_State& ui_state)
{
    return (ui_state.click && is_coord_inside_rect(ui_state.cx, ui_state.cy, rect));
}

bool is_mousedown_event_inside_rect(
    Rect& rect,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
) {
    return (
        is_event(Event::Mousedown, ui_state, prev_ui_state)
        && is_coord_inside_rect(ui_state.cx, ui_state.cy, rect)
    );
}

bool is_mouseup_event_inside_rect(
    Rect& rect,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
) {
    return (
        is_event(Event::Mouseup, ui_state, prev_ui_state)
        && is_coord_inside_rect(ui_state.cx, ui_state.cy, rect)
    );
}

bool is_event(Event event, Ui_State& ui_state, Ui_State& prev_ui_state)
{
    switch (event) {
    case Event::Space:
        return (ui_state.space && !prev_ui_state.space);
    case Event::Tab:
        return (ui_state.tab && !prev_ui_state.tab);
    case Event::Mouseup:
        return (!ui_state.click && prev_ui_state.click);
    case Event::Mousedown:
        return (ui_state.click && !prev_ui_state.click);
    default:
        return false;
    }
}

bool is_coord_inside_rect(int x, int y, Rect rect)
{
    return (
        x >= rect.x &&
        y >= rect.y &&
        x <= rect.x + rect.w &&
        y <= rect.y + rect.h
    );
}

bool is_coord_inside_rect(Coord coord, Rect rect)
{
    return (
        coord.x >= rect.x &&
        coord.y >= rect.y &&
        coord.x <= rect.x + rect.w &&
        coord.y <= rect.y + rect.h
    );
}

int clamp(int x, int min, int max)
{
    if (x < min) {
        return min;
    } else if ( x >= max) {
        return max - 1;
    } else {
        return x;
    }
}

void update(int& x, int delta, int min, int max)
{
    x = clamp(x + delta, min, max);
}

void increment(int& x, int min, int max)
{
    x = clamp(x + 1, min, max);
}

void decrement(int& x, int min, int max)
{
    x = clamp(x - 1, min, max);
}

Rect get_text_rect(std::string text, Coord coord, Store& store)
{
    Rect rect{
        coord.x,
        coord.y,
        text.size() * store.font_width,
        store.font_size
    };
    return rect;
}
