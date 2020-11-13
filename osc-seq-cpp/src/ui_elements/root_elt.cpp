#include "root_elt.hpp"

#include "../store/coord.hpp"
#include "bpm_elt.hpp"
#include "event_editor_elt.hpp"
#include "grid_elt.hpp"
#include "seq_grid_elt.hpp"

void root_elt(Store& store) {
    Coord seq_grid_coord = { 30, 30 };
    seq_grid_elt(
        seq_grid_coord,
        store.seq_grid,
        store,
        []() {}
    );

    Coord bpm_coord = { 200, 200 };
    bpm_elt("bpm1", bpm_coord, store.bpm, store, []() {});

    Coord header_coord = { 800, 50 };
    event_editor_elt(header_coord, store);
}
