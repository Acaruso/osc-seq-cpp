#pragma once

#include <functional>
#include <string>
#include <vector>

#include "grid.hpp"
#include "grid_cell.hpp"
#include "pattern_grid.hpp"
#include "pattern_grid_cell.hpp"
#include "../ui_state.hpp"

struct Row_Metadata
{
    bool mute;
    Grid_Cell default_grid_cell;
};

struct Seq_Grid
{
    int selected_row;
    int selected_col;

    int selected_target_row;
    int selected_target_col;

    int num_patterns;
    int selected_pattern;

    Event_Grid clock_grid;

    std::vector<Grid<Grid_Cell>> pattern_bank;

    // std::vector<std::vector<Row_Metadata>> row_metadata;
    std::vector<Row_Metadata> row_metadata;

    Seq_Grid() {}

    Seq_Grid(int numRows, int numCols, int rect_w, int rect_h);

    Grid_Cell& get_selected_cell();

    Grid_Cell get_selected_cell_copy();

    Event_Grid& get_selected_pattern();

    Event_Grid get_selected_pattern_copy();

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

    Row_Metadata& get_row_metadata(int row);

    Grid_Cell& get_default_grid_cell();

    Grid_Cell get_default_grid_cell_copy();

    void toggle_row_mute(int row);

    void clear_row();

    void rotate_row_right();

    void rotate_row_left();

    void shift_row_right();

    void shift_row_left();
};
