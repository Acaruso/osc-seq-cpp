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

    clock_grid = Event_Grid{1, numCols, rect_w, clock_grid_rect_h};

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

    for (int i = 0; i < numRows; ++i) {
        Grid_Cell gc{i};
        gc.toggled = true;
        row_metadata.push_back({ false, 0, gc });
    }
}

Grid_Cell& Seq_Grid::get_selected_cell()
{
    return pattern_bank[selected_pattern].data[selected_row][selected_col];
}

Grid_Cell Seq_Grid::get_selected_cell_copy()
{
    return pattern_bank[selected_pattern].data[selected_row][selected_col];
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
}

void Seq_Grid::set_toggled(
    int row,
    int col,
    Ui_State& ui_state,
    Event_Editor& event_editor
) {
    // need these for click action
    selected_row = row;
    selected_col = col;

    // use lshift + click to select cell but not toggle it
    if (!ui_state.lshift) {
        auto& grid_cell = get_selected_cell();

        if (!grid_cell.toggled) {
            grid_cell = get_default_grid_cell_copy();
            grid_cell.toggled = true;
            auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
            target.first.data = selected_row;
            target.second.data = selected_col;
        } else if (grid_cell.toggled) {
            grid_cell = Grid_Cell{selected_row};
            event_editor.selected_row = 0;
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

    row_metadata.push_back({ false, 0, Grid_Cell{channel} });
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

void Seq_Grid::increment_selected_row(Event_Editor& event_editor)
{
    auto& pattern = get_selected_pattern();
    increment(selected_row, 0, pattern.numRows);
    event_editor.selected_row = 0;
}

void Seq_Grid::decrement_selected_row(Event_Editor& event_editor)
{
    auto& pattern = get_selected_pattern();
    decrement(selected_row, 0, pattern.numRows);
    event_editor.selected_row = 0;
}

void Seq_Grid::increment_selected_col(Event_Editor& event_editor)
{
    auto& pattern = get_selected_pattern();
    increment(selected_col, 0, pattern.numCols);
    event_editor.selected_row = 0;
}

void Seq_Grid::decrement_selected_col(Event_Editor& event_editor)
{
    auto& pattern = get_selected_pattern();
    decrement(selected_col, 0, pattern.numCols);
    event_editor.selected_row = 0;
}

void Seq_Grid::increment_selected_target_row()
{
    auto& pattern = get_selected_pattern();
    increment(selected_target_row, 0, pattern.numRows);
    auto& grid_cell = get_selected_cell();
    auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
    target.first.data = selected_target_row;
    target.second.data = selected_target_col;
}

void Seq_Grid::decrement_selected_target_row()
{
    auto& pattern = get_selected_pattern();
    decrement(selected_target_row, 0, pattern.numRows);
    auto& grid_cell = get_selected_cell();
    auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
    target.first.data = selected_target_row;
    target.second.data = selected_target_col;
}

void Seq_Grid::increment_selected_target_col()
{
    auto& pattern = get_selected_pattern();
    increment(selected_target_col, 0, pattern.numCols);
    auto& grid_cell = get_selected_cell();
    auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
    target.first.data = selected_target_row;
    target.second.data = selected_target_col;
}

void Seq_Grid::decrement_selected_target_col()
{
    auto& pattern = get_selected_pattern();
    decrement(selected_target_col, 0, pattern.numCols);
    auto& grid_cell = get_selected_cell();
    auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
    target.first.data = selected_target_row;
    target.second.data = selected_target_col;
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

std::string Seq_Grid::serialize()
{
    std::ostringstream ss;

    ss << "PATTERN BANK" << std::endl;
    ss << num_patterns << std::endl;
    ss << pattern_bank[0].numRows << std::endl;
    ss << pattern_bank[0].numCols << std::endl;
    for (auto& pattern : pattern_bank) {
        for (auto& row : pattern.data) {
            for (auto& cell : row) {
                ss << cell.serialize() << std::endl;
            }
        }
    }

    ss << "ROW METADATA" << std::endl;
    ss << row_metadata.size() << std::endl;
    for (auto& elt : row_metadata) {
        ss << elt.serialize() << std::endl;
    }

    return ss.str();
}

void Seq_Grid::deserialize(std::ifstream& fs)
{
    std::string str;
    std::getline(fs, str);      // "PATTERN BANK"
    std::getline(fs, str);
    num_patterns = atoi(str.c_str());
    std::getline(fs, str);
    int num_rows = atoi(str.c_str());
    std::getline(fs, str);
    int num_cols = atoi(str.c_str());

    selected_row = 0;
    selected_col = 0;
    selected_target_row = 0;
    selected_target_col = 0;
    selected_pattern = 0;

    int clock_grid_rect_h = rect_h / 2;

    clock_grid = Event_Grid{1, num_cols, rect_w, clock_grid_rect_h};

    // clear pattern_bank
    pattern_bank = std::vector<Grid<Grid_Cell>>();

    for (int i = 0; i < num_patterns; ++i) {
        Grid<Grid_Cell> grid = Grid<Grid_Cell>{num_rows, num_cols, rect_w, rect_h};

        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                auto& elt = grid.data[row][col];
                elt.deserialize(fs);
            }
        }

        pattern_bank.push_back(grid);
    }

    std::getline(fs, str);      // "ROW METADATA"
    std::getline(fs, str);
    int row_metadata_size = atoi(str.c_str());
    row_metadata = std::vector<Row_Metadata>();
    for (int i = 0; i < row_metadata_size; ++i) {
        Row_Metadata elt;
        elt.deserialize(fs);
        row_metadata.push_back(elt);
    }
}

std::string Row_Metadata::serialize()
{
    std::ostringstream ss;
    ss << mute << std::endl;
    ss << default_grid_cell.serialize();
    return ss.str();
}

void Row_Metadata::deserialize(std::ifstream& fs)
{
    std::string str;
    std::getline(fs, str);
    mute = atoi(str.c_str());
    default_grid_cell.deserialize(fs);
}
