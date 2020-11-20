#include "grid_cell_elt.hpp"

#include "../store/coord.hpp"
#include "image_elt.hpp"
#include "text_elt.hpp"

void grid_cell_elt(
    Image_Set image_set,
    Grid_Cell& grid_cell,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
) {
    image_elt_clickable_toggleable(
        image_set,
        grid_cell.toggled,
        coord,
        store,
        on_click
    );

    if (grid_cell.has_meta) {
        Coord text_coord = { coord.x + 5, coord.y };
        text_elt(
            "m",
            text_coord,
            store
        );
    }
}
