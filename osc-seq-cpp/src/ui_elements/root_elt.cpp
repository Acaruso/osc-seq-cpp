#include "root_elt.hpp"

#include "../filesystem/filesystem.hpp"
#include "../store/coord.hpp"
#include "../windows/windows_wrapper.hpp"
#include "bpm_elt.hpp"
#include "event_editor_elt.hpp"
#include "grid/grid_elt.hpp"
#include "grid/pattern_grid_elt.hpp"
#include "grid/seq_grid_elt.hpp"
#include "image_elt.hpp"
#include "load_save_elt.hpp"
#include "registers_elt.hpp"

#include <string>
#include <iostream>

void root_elt(Store& store)
{
    Coord event_editor_coord = { 30, 50 };
    event_editor_wrapper_elt(event_editor_coord, store);

    Coord button_minus_coord = { 335, 44 }; // +40
    image_elt_clickable(
        store.images["button-minus"],
        button_minus_coord,
        store,
        [&]() { store.seq_grid.pop_row(); }
    );

    Coord button_plus_coord = { 335, 68 };
    image_elt_clickable(
        store.images["button-plus"],
        button_plus_coord,
        store,
        [&]() { store.seq_grid.add_row(); }
    );

    Coord seq_grid_coord = { 360, 40 };
    seq_grid_elt(
        seq_grid_coord,
        store.seq_grid,
        store,
        []() {}
    );

    Coord bpm_coord = { 360, 0 };
    bpm_elt("bpm1", bpm_coord, store.bpm, store, []() {});

    Coord reg_coord = { 650, 8 };
    registers_elt(reg_coord, store);

    Coord pattern_grid_coord = { 1190, 40 };
    pattern_grid_elt(
        pattern_grid_coord,
        2,
        store.pattern_grid,
        store,
        []() {}
    );

    Coord save_coord = Coord{ 1410, 40 };
    button_load_save_elt(
        "Save",
        store.images["button-load-save"],
        save_coord,
        store,
        [&]() {
            std::string path = save_file_dialog();
            save_file(path, store);
        }
    );

    Coord load_coord = Coord{ 1410, 74 };
    button_load_save_elt(
        "Load",
        store.images["button-load-save"],
        load_coord,
        store,
        [&]() {
            std::string path = open_file_dialog();
            open_file(path, store);
        }
    );
}
