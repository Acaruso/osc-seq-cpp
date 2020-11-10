#include "bpm_elt.hpp"

#include <string>

#include "image_elt.hpp"
#include "text_elt.hpp"

void bpm_elt(
    Store& store,
    Coord& coord,
    std::function<void()> on_click
) {
    Coord arrow_up_coord = { coord.x, coord.y };

    image_elt(
        store.images["arrow-up"],
        arrow_up_coord,
        store.ui_state,
        store.window_renderer,
        [&]() { ++store.bpm; }
    );

    Coord arrow_down_coord = { coord.x, coord.y + 18 };

    image_elt(
        store.images["arrow-down"],
        arrow_down_coord,
        store.ui_state,
        store.window_renderer,
        [&]() { --store.bpm; }
    );

    Coord text_coord = { coord.x + 33, coord.y + 8 };

    text_elt(
        store.fonts["dos"],
        std::to_string(store.bpm),
        text_coord,
        store.ui_state,
        store.window_renderer,
        []() {}
    );
}
