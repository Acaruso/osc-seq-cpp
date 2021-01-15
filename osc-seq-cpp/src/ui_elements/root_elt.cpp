#include "root_elt.hpp"

#include "../filesystem/filesystem.hpp"
#include "../store/coord.hpp"
#include "../windows/windows_wrapper.hpp"
#include "arrow_up_down_elt.hpp"
#include "event_editor/event_editor_elt.hpp"
#include "grid/grid_elt.hpp"
#include "grid/pattern_grid_elt.hpp"
#include "grid/seq_grid_elt.hpp"
#include "image_elt.hpp"
#include "load_save_elt.hpp"
#include "pages_elt.hpp"
#include "registers_elt.hpp"
#include "../util.hpp"

#include <string>
#include <iostream>

void root_elt(Store& store)
{
    Coord event_editor_coord = { 30, 50 };
    event_editor_wrapper_elt(event_editor_coord, store);

    Coord button_minus_coord = { 335, 44 };
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
    arrow_up_down_elt(
        "bpm",
        "bpm: ",
        bpm_coord,
        store.bpm,
        store,
        [&]() { ++store.bpm; },
        [&]() { --store.bpm; },
        [&](int drag_amount) { store.bpm += drag_amount; }
    );

    Coord pages_coord = { 500, 0 };
    arrow_up_down_elt(
        "page",
        "page: ",
        pages_coord,
        store.seq_grid.selected_page,
        store,
        [&]() {
            store.seq_grid.increment_selected_page();
        },
        [&]() {
            store.seq_grid.decrement_selected_page();
        },
        [](int x) {}
    );

    Coord num_steps_coord = { 630, 0 };
    arrow_up_down_elt(
        "num_steps",
        "num steps: ",
        num_steps_coord,
        store.seq_grid.get_selected_pattern().numCols,
        store,
        [&]() {
            int numCols = store.seq_grid.get_selected_pattern().numCols;
            if (numCols == 64) {
                return;
            } else {
                store.seq_grid.add_cols(16);
            }
        },
        [&]() {
            int numCols = store.seq_grid.get_selected_pattern().numCols;
            if (numCols == 16) {
                return;
            } else {
                store.seq_grid.pop_cols(16);
            }
        },
        [](int x) {}
    );

    Coord reg_coord = { 820, 8 };
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
