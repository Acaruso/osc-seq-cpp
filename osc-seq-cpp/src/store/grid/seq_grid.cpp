#include "seq_grid.hpp"

#include "../../util.hpp"

Seq_Grid::Seq_Grid(int numRows, int numCols, int rect_w, int rect_h)
    : selected_row(0), selected_col(0),
    selected_target_row(0), selected_target_col(0),
    num_patterns(8), selected_pattern(0)
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
}

Grid_Cell& Seq_Grid::get_selected_cell()
{
    return pattern_bank[selected_pattern].data[selected_row][selected_col];
}

Event_Grid& Seq_Grid::get_selected_pattern()
{
    return pattern_bank[selected_pattern];
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
    auto& pattern = get_selected_pattern();
    int channel = pattern.data.size();

    std::vector<Grid_Cell> v;
    for (int k = 0; k < pattern.numCols; k++) {
        v.push_back(Grid_Cell(channel));
    }
    pattern.data.push_back(v);
    ++pattern.numRows;
}

void Seq_Grid::pop_row()
{
    auto& pattern = get_selected_pattern();
    if (pattern.numRows <= 1) {
        return;
    } else {
        pattern.data.pop_back();
        --pattern.numRows;
    }
}

void Seq_Grid::increment_selected_row(Event_Editor& event_editor)
{
    auto& pattern = get_selected_pattern();
    selected_row = clamp(
        selected_row + 1,
        0,
        pattern.numRows
    );
    event_editor.selected_row = 0;
}

void Seq_Grid::decrement_selected_row(Event_Editor& event_editor)
{
    auto& pattern = get_selected_pattern();
    selected_row = clamp(
        selected_row - 1,
        0,
        pattern.numRows
    );
    event_editor.selected_row = 0;
}

void Seq_Grid::increment_selected_col(Event_Editor& event_editor)
{
    auto& pattern = get_selected_pattern();
    selected_col = clamp(
        selected_col + 1,
        0,
        pattern.numCols
    );
    event_editor.selected_row = 0;
}

void Seq_Grid::decrement_selected_col(Event_Editor& event_editor)
{
    auto& pattern = get_selected_pattern();
    selected_col = clamp(
        selected_col - 1,
        0,
        pattern.numCols
    );
    event_editor.selected_row = 0;
}

void Seq_Grid::increment_selected_target_row()
{
    auto& pattern = get_selected_pattern();
    selected_target_row = clamp(
        selected_target_row + 1,
        0,
        pattern.numRows
    );
    auto& grid_cell = get_selected_cell();
    auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
    target.first.data = selected_target_row;
    target.second.data = selected_target_col;
}

void Seq_Grid::decrement_selected_target_row()
{
    auto& pattern = get_selected_pattern();
    selected_target_row = clamp(
        selected_target_row - 1,
        0,
        pattern.numRows
    );
    auto& grid_cell = get_selected_cell();
    auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
    target.first.data = selected_target_row;
    target.second.data = selected_target_col;
}

void Seq_Grid::increment_selected_target_col()
{
    auto& pattern = get_selected_pattern();
    selected_target_col = clamp(
        selected_target_col + 1,
        0,
        pattern.numCols
    );
    auto& grid_cell = get_selected_cell();
    auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
    target.first.data = selected_target_row;
    target.second.data = selected_target_col;
}

void Seq_Grid::decrement_selected_target_col()
{
    auto& pattern = get_selected_pattern();
    selected_target_col = clamp(
        selected_target_col - 1,
        0,
        pattern.numCols
    );
    auto& grid_cell = get_selected_cell();
    auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
    target.first.data = selected_target_row;
    target.second.data = selected_target_col;
}
