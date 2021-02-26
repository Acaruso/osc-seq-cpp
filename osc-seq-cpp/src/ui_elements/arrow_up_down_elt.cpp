#include "arrow_up_down_elt.hpp"

#include <string>

#include "image_elt.hpp"
#include "text_elt.hpp"

void arrow_up_down_elt(
    std::string id,
    std::string text,
    Coord& coord,
    int& val,
    Store& store,
    std::function<void()> on_up_click,
    std::function<void()> on_down_click,
    std::function<void(int)> on_drag
) {
    Coord arrow_up_coord = { coord.x, coord.y };

    image_elt_clickable(
        store.images["arrow-up"],
        arrow_up_coord,
        store,
        on_up_click
    );

    Coord arrow_down_coord = { coord.x, coord.y + 18 };

    image_elt_clickable(
        store.images["arrow-down"],
        arrow_down_coord,
        store,
        on_down_click
    );

    Coord text_coord = { coord.x + 33, coord.y + 8 };

    text_elt_draggable(
        id + "/text",
        text + std::to_string(val),
        text_coord,
        store,
        []() {},
        on_drag
    );
}
