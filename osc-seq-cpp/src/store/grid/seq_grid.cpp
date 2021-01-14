#include "seq_grid.hpp"

#include "../../util.hpp"

#include <iostream>
#include <sstream>

Seq_Grid::Seq_Grid(int num_patterns, int numRows, int numCols, int rect_w, int rect_h)
    : selected_row(0), selected_col(0),
    selected_target_row(0), selected_target_col(0),
    num_patterns(num_patterns), selected_pattern(0),
    rect_w(rect_w), rect_h(rect_h)
{
    int clock_grid_rect_h = rect_h / 2;

    // init clock_grid
    clock_grid = Event_Grid{1, numCols, rect_w, clock_grid_rect_h};

    // init pattern_bank
    for (int i = 0; i < num_patterns; ++i) {
        Event_Grid grid = Event_Grid(numRows, numCols, rect_w, rect_h);

        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                auto& elt = grid.data[row][col];
                elt.channel = row;
            }
        }

        pattern_bank.push_back(grid);
    }

    // init row_metadata
    for (int i = 0; i < numRows; ++i) {
        Grid_Cell gc{i};
        gc.toggled = true;
        row_metadata.push_back({ false, 0, gc });
    }
}

Grid_Cell& Seq_Grid::get_selected_cell()
{
    int data_col = selected_col + (selected_page * page_size);
    return pattern_bank[selected_pattern].data[selected_row][data_col];
}

Grid_Cell Seq_Grid::get_selected_cell_copy()
{
    int data_col = selected_col + (selected_page * page_size);
    return pattern_bank[selected_pattern].data[selected_row][data_col];
}

Event_Grid& Seq_Grid::get_selected_pattern()
{
    return pattern_bank[selected_pattern];
}

Event_Grid Seq_Grid::get_selected_pattern_copy()
{
    return pattern_bank[selected_pattern];
}

void Seq_Grid::set_selected_pattern(Pattern_Grid& pg)
{
    selected_pattern = (pg.selected_row * pg.num_cols) + pg.selected_col;
    selected_page = 0;
}

void Seq_Grid::set_toggled(
    int row,
    int display_col,
    Ui_State& ui_state,
    Event_Editor& event_editor
) {
    // need these for click action
    selected_row = row;
    // selected_col = col;
    selected_col = display_col;
    int data_col = display_col + (selected_page * page_size);

    // use lshift + click to select cell but not toggle it
    if (!ui_state.lshift) {
        auto& grid_cell = get_selected_cell();

        if (!grid_cell.toggled) {
            grid_cell = get_default_grid_cell_copy();
            grid_cell.toggled = true;

            auto mod_fields = grid_cell.get_fields_by_flag(Mod_Field);
            for (auto& field : mod_fields) {
                auto& target_row = field->get_subfield<Int_Subfield>("target_row");
                auto& target_col = field->get_subfield<Int_Subfield>("target_col");
                target_row.data = selected_row;
                target_col.data = data_col;
            }
        } else if (grid_cell.toggled) {
            grid_cell = Grid_Cell{selected_row};
            ui_state.mode = Normal;
        }
    }
}

void Seq_Grid::add_row()
{
    for (auto& pattern : pattern_bank) {
        int channel = pattern.data.size();
        pattern.data.push_back(
            std::vector<Grid_Cell>(pattern.numCols, Grid_Cell(channel))
        );
        ++pattern.numRows;
    }

    int channel = pattern_bank[0].data.size() - 1;

    Grid_Cell gc{channel};
    gc.toggled = true;
    row_metadata.push_back({ false, 0, gc });
}

void Seq_Grid::pop_row()
{
    for (auto& pattern : pattern_bank) {
        if (pattern.numRows <= 1) {
            return;
        } else {
            pattern.data.pop_back();
            --pattern.numRows;
        }
    }

    row_metadata.pop_back();
}

void Seq_Grid::add_cols(int num_cols)
{
    auto& pattern = get_selected_pattern();

    for (int row_num = 0; row_num < pattern.data.size(); ++row_num) {
        auto& row = pattern.data[row_num];
        for (int i = 0; i < num_cols; ++i) {
            Grid_Cell gc = get_default_grid_cell_copy(row_num);
            gc.toggled = false;
            row.push_back(gc);
        }
    }
    pattern.numCols += num_cols;
}

void Seq_Grid::pop_cols(int num_cols)
{
    auto& pattern = get_selected_pattern();
    for (auto& row : pattern.data) {
        row.erase(row.end() - num_cols, row.end());
    }
    pattern.numCols -= num_cols;
}

void Seq_Grid::increment_selected_row()
{
    auto& pattern = get_selected_pattern();
    increment(selected_row, 0, pattern.numRows);
}

void Seq_Grid::decrement_selected_row()
{
    auto& pattern = get_selected_pattern();
    decrement(selected_row, 0, pattern.numRows);
}

void Seq_Grid::increment_selected_col()
{
    auto& pattern = get_selected_pattern();
    increment(selected_col, 0, pattern.numCols);
}

void Seq_Grid::decrement_selected_col()
{
    auto& pattern = get_selected_pattern();
    decrement(selected_col, 0, pattern.numCols);
}

void Seq_Grid::increment_selected_target_row(Event_Editor& ee)
{
    auto& p = get_selected_pattern();
    update_selected_target(selected_target_row, 1, 0, p.numRows, ee);
}

void Seq_Grid::decrement_selected_target_row(Event_Editor& ee)
{
    auto& p = get_selected_pattern();
    update_selected_target(selected_target_row, -1, 0, p.numRows, ee);
}

void Seq_Grid::increment_selected_target_col(Event_Editor& ee)
{
    auto& p = get_selected_pattern();
    update_selected_target(selected_target_col, 1, 0, p.numCols, ee);
}

void Seq_Grid::decrement_selected_target_col(Event_Editor& ee)
{
    auto& p = get_selected_pattern();
    update_selected_target(selected_target_col, -1, 0, p.numCols, ee);
}

void Seq_Grid::update_selected_target(
    int& v,
    int delta,
    int min,
    int max,
    Event_Editor& ee
) {
    auto& pattern = get_selected_pattern();
    update(v, delta, min, max);

    auto& grid_cell = get_selected_cell();
    auto& field = grid_cell.get_selected_event_field(ee);

    auto& target_row = field.get_subfield<Int_Subfield>("target_row");
    auto& target_col = field.get_subfield<Int_Subfield>("target_col");
    target_row.data = selected_target_row;
    target_col.data = selected_target_col + (selected_page * page_size);
}

Row_Metadata& Seq_Grid::get_row_metadata(int row)
{
    return row_metadata[row];
}

Grid_Cell& Seq_Grid::get_default_grid_cell()
{
    return get_row_metadata(selected_row).default_grid_cell;
}

Grid_Cell Seq_Grid::get_default_grid_cell_copy()
{
    return get_row_metadata(selected_row).default_grid_cell;
}

Grid_Cell Seq_Grid::get_default_grid_cell_copy(int row)
{
    return get_row_metadata(row).default_grid_cell;
}

void Seq_Grid::toggle_row_mute(int row)
{
    if (row >= row_metadata.size()) {
        return;
    }
    auto& metadata = get_row_metadata(row);
    metadata.mute = !metadata.mute;
}

void Seq_Grid::clear_row()
{
    auto& pattern = get_selected_pattern();
    auto& row = pattern.data[selected_row];
    for (auto& cell : row) {
        cell = Grid_Cell{};
        cell.channel = selected_row;
    }
}

void Seq_Grid::rotate_row_right()
{
    auto& pattern = get_selected_pattern();
    auto& row = pattern.data[selected_row];
    auto temp = row[row.size() - 1];
    for (int i = row.size() - 2; i >= 0; --i) {
        row[i + 1] = row[i];
    }
    row[0] = temp;
}

void Seq_Grid::rotate_row_left()
{
    auto& pattern = get_selected_pattern();
    auto& row = pattern.data[selected_row];
    auto temp = row[0];
    for (int i = 1; i < row.size(); ++i) {
        row[i - 1] = row[i];
    }
    row[row.size() - 1] = temp;
}

void Seq_Grid::shift_row_right()
{
    auto& pattern = get_selected_pattern();
    auto& row = pattern.data[selected_row];
    for (int i = row.size() - 2; i >= 0; --i) {
        row[i + 1] = row[i];
    }
    row[0] = Grid_Cell{selected_row};
}

void Seq_Grid::shift_row_left()
{
    auto& pattern = get_selected_pattern();
    auto& row = pattern.data[selected_row];
    for (int i = 1; i < row.size(); ++i) {
        row[i - 1] = row[i];
    }
    row[row.size() - 1] = Grid_Cell{selected_row};
}
