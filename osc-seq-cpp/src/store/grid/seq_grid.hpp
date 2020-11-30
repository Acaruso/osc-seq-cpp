#pragma once

#include <functional>
#include <string>
#include <vector>

#include "grid.hpp"
#include "grid_cell.hpp"
#include "pattern_grid.hpp"
#include "pattern_grid_cell.hpp"
#include "../ui_state.hpp"

struct Seq_Grid
{
    int selected_row;
    int selected_col;

    int selected_target_row;
    int selected_target_col;

    int num_patterns;
    int selected_pattern;

    Event_Grid clock_grid;

    std::vector<Event_Grid> pattern_bank;

    // Event_Grid clickable_grid;

    Seq_Grid() {}

    Seq_Grid(int numRows, int numCols, int rect_w, int rect_h);

    Grid_Cell& get_selected_cell();

    Event_Grid& get_selected_pattern();

    void set_selected_pattern(Pattern_Grid& pattern_grid);

    void set_toggled(
        int row,
        int col,
        Ui_State& ui_state,
        Event_Editor& event_editor
    );

    void add_row();

    void pop_row();

    void increment_selected_row(Event_Editor& event_editor);

    void decrement_selected_row(Event_Editor& event_editor);

    void increment_selected_col(Event_Editor& event_editor);

    void decrement_selected_col(Event_Editor& event_editor);

    void increment_selected_target_row();

    void decrement_selected_target_row();

    void increment_selected_target_col();

    void decrement_selected_target_col();
};