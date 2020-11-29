#include "grid_cell_elt.hpp"

#include "../store/coord.hpp"
#include "image_elt.hpp"
#include "text_elt.hpp"

void grid_cell_elt(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
) {

    image_elt_clickable_toggleable(
        image_set,
        toggled,
        coord,
        store,
        on_click
    );
}
