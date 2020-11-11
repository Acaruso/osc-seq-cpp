#include "bpm_elt.hpp"

#include <string>

#include "image_elt.hpp"
#include "text_elt.hpp"

void bpm_elt(
    std::string id,
    Coord& coord,
    int& bpm,
    Store& store,
    std::function<void()> on_click
) {
    Coord arrow_up_coord = { coord.x, coord.y };

    image_elt(
        store.images["arrow-up"],
        arrow_up_coord,
        store.ui_state,
        store.window_renderer,
        [&]() { ++bpm; }
    );

    Coord arrow_down_coord = { coord.x, coord.y + 18 };

    image_elt(
        store.images["arrow-down"],
        arrow_down_coord,
        store.ui_state,
        store.window_renderer,
        [&]() { --bpm; }
    );

    Coord text_coord = { coord.x + 33, coord.y + 8 };

    text_elt(
        id + "/text",
        store.fonts["dos"],
        std::to_string(bpm) + " bpm",
        text_coord,
        store.ui_state,
        store.window_renderer,
        []() {},
        [&](int drag_amount) { bpm += drag_amount; }
    );
}
