#include "deserialize.hpp"

#include <iostream>

void deserialize_store(Store& store, std::ifstream& fs)
{
    std::string str;
    std::getline(fs, str);  // BPM
    store.bpm = atoi(str.c_str());
    deserialize_seq_grid(store.seq_grid, fs);
}

void deserialize_seq_grid(Seq_Grid& seq_grid, std::ifstream& fs)
{
    std::string str;
    std::getline(fs, str);      // "PATTERN BANK"
    std::getline(fs, str);
    seq_grid.num_patterns = atoi(str.c_str());
    std::getline(fs, str);
    int num_rows = atoi(str.c_str());
    std::getline(fs, str);
    int num_cols = atoi(str.c_str());

    seq_grid.selected_row = 0;
    seq_grid.selected_col = 0;
    seq_grid.selected_target_row = 0;
    seq_grid.selected_target_col = 0;
    seq_grid.selected_pattern = 0;

    int clock_grid_rect_h = seq_grid.rect_h / 2;

    seq_grid.clock_grid = Event_Grid{1, num_cols, seq_grid.rect_w, clock_grid_rect_h};

    // clear pattern_bank
    seq_grid.pattern_bank = std::vector<Grid<Grid_Cell>>();

    for (int i = 0; i < seq_grid.num_patterns; ++i) {
        Grid<Grid_Cell> grid = Grid<Grid_Cell>{num_rows, num_cols, seq_grid.rect_w, seq_grid.rect_h};

        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                auto& grid_cell = grid.data[row][col];
                deserialize_grid_cell(grid_cell, fs);
            }
        }

        seq_grid.pattern_bank.push_back(grid);
    }

    // std::getline(fs, str);      // "ROW METADATA"
    // std::getline(fs, str);
    // int row_metadata_size = atoi(str.c_str());
    // row_metadata = std::vector<Row_Metadata>();
    // for (int i = 0; i < row_metadata_size; ++i) {
    //     Row_Metadata elt;
    //     elt.deserialize(fs);
    //     row_metadata.push_back(elt);
    // }
}

void deserialize_grid_cell(Grid_Cell& grid_cell, std::ifstream& fs)
{
    std::string line;
    std::getline(fs, line);
    std::stringstream ss{line};

    std::string token;

    // toggled
    std::getline(ss, token, ',');
    grid_cell.toggled = atoi(token.c_str());

    // channel
    std::getline(ss, token, ' ');
    std::getline(ss, token, ',');
    grid_cell.channel = atoi(token.c_str());

    // // retrigger
    // std::getline(ss, token, ' ');
    // std::getline(ss, token, ',');
    // grid_cell.channel = atoi(token.c_str());

    for (auto& tab : grid_cell.tabs) {
        for (auto& field : tab.fields) {
            for (auto& subfield : field.subfields) {
                if (auto v = std::get_if<Int_Subfield>(&subfield)) {
                    std::getline(ss, token, ' ');
                    std::getline(ss, token, ',');
                    v->data = atoi(token.c_str());
                } else if (auto v = std::get_if<Options_Subfield>(&subfield)) {
                    std::getline(ss, token, ' ');
                    std::getline(ss, token, ',');
                    v->selected = atoi(token.c_str());

                    std::getline(ss, token, ' ');
                    std::getline(ss, token, ',');
                    v->subfield_path.tab_key = token;

                    std::getline(ss, token, ' ');
                    std::getline(ss, token, ',');
                    v->subfield_path.field_key = token;

                    std::getline(ss, token, ' ');
                    std::getline(ss, token, ',');
                    v->subfield_path.subfield_key = token;
                }
            }
        }
    }

}
