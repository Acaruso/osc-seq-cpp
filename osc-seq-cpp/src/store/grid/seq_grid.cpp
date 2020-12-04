#include "seq_grid.hpp"

#include "../../util.hpp"

Seq_Grid::Seq_Grid(int numRows, int numCols, int rect_w, int rect_h)
    : selected_row(0), selected_col(0),
    selected_target_row(0), selected_target_col(0),
    num_patterns(16), selected_pattern(0)
{
    int clock_grid_rect_h = rect_h / 2;

    clock_grid = Event_Grid(1, numCols, rect_w, clock_grid_rect_h);

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

    row_metadata.resize(
        num_patterns,
        std::vector<Row_Metadata>(numRows, { false })
    );
}

Grid_Cell& Seq_Grid::get_selected_cell()
{
    return pattern_bank[selected_pattern].data[selected_row][selected_col];
}

Event_Grid& Seq_Grid::get_selected_pattern()
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
    selected_row = row;
    selected_col = col;

    if (!ui_state.lshift) {
        auto& grid_cell = get_selected_cell();

        if (!grid_cell.toggled) {
            grid_cell.toggled = true;
            auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
            target.first.data = row;
            target.second.data = col;
        } else if (grid_cell.toggled) {
            grid_cell.toggled = false;
            grid_cell.init_all_event_fields();
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

    for (auto& pattern : row_metadata) {
        pattern.push_back({ false });
    }
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

    for (auto& pattern : row_metadata) {
        pattern.pop_back();
    }
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
    return row_metadata[selected_pattern][row];
}

void Seq_Grid::toggle_row_mute(int row)
{
    auto& x = row_metadata[selected_pattern];
    if (row >= x.size()) {
        return;
    }
    x[row].mute = !x[row].mute;
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

void Seq_Grid::shift_row_right()
{
    auto& pattern = get_selected_pattern();
    auto& row = pattern.data[selected_row];
    for (int i = row.size() - 2; i >= 0; --i) {
        row[i + 1] = row[i];
    }
    row[0] = Grid_Cell{};
}

void Seq_Grid::shift_row_left()
{
    auto& pattern = get_selected_pattern();
    auto& row = pattern.data[selected_row];
    for (int i = row.size() - 2; i >= 0; --i) {
        row[i + 1] = row[i];
    }
    row[0] = Grid_Cell{};
}
