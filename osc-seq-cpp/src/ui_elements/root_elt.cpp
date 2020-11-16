#include "root_elt.hpp"

#include "../store/coord.hpp"
#include "bpm_elt.hpp"
#include "event_editor_elt.hpp"
#include "grid_elt.hpp"
#include "image_elt.hpp"
#include "seq_grid_elt.hpp"

void root_elt(Store& store) {
    Coord seq_grid_coord = { 270, 40 };
    // Coord seq_grid_coord = { 30, 40 };
    seq_grid_elt(
        seq_grid_coord,
        store.seq_grid,
        store,
        []() {}
    );

    Coord button_minus_coord = { 245, 44 };
    // Coord button_minus_coord = { 5, 44 };
    image_elt_clickable(
        store.images["button-minus"],
        button_minus_coord,
        store,
        [&]() { store.seq_grid.pop_row(); }
    );

    Coord button_plus_coord = { 245, 68 };
    // Coord button_plus_coord = { 5, 68 };
    image_elt_clickable(
        store.images["button-plus"],
        button_plus_coord,
        store,
        [&]() { store.seq_grid.add_row(); }
    );

    Coord bpm_coord = { 270, 0 };
    // Coord bpm_coord = { 30, 0 };
    bpm_elt("bpm1", bpm_coord, store.bpm, store, []() {});

    Coord editor_coord = { 30, 50 };
    // Coord editor_coord = { 800, 50 };
    event_editor_elt(editor_coord, store);
}
