#include "load_save_elt.hpp"

#include "image_elt.hpp"
#include "text_elt.hpp"

#include <string>

void button_load_save_elt(
    std::string text,
    Image_Set& image_set,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
) {
    image_elt_clickable(
        image_set,
        coord,
        store,
        on_click
    );

    Coord load_text_coord = { coord.x + 8, coord.y + 8 };
    text_elt(text, load_text_coord, store);
}
