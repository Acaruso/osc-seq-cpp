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

    image_elt_clickable(
        store.images["arrow-up"],
        arrow_up_coord,
        store,
        [&]() { ++bpm; }
    );

    Coord arrow_down_coord = { coord.x, coord.y + 18 };

    image_elt_clickable(
        store.images["arrow-down"],
        arrow_down_coord,
        store,
        [&]() { --bpm; }
    );

    Coord text_coord = { coord.x + 33, coord.y + 8 };

    text_elt_draggable(
        id + "/text",
        std::to_string(bpm) + " bpm",
        text_coord,
        store,
        []() {},
        [&](int drag_amount) { bpm += drag_amount; }
    );
}
