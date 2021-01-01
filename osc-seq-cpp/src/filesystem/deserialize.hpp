#pragma once

#include "../store/grid/seq_grid.hpp"
#include "../store/grid/tab.hpp"
#include "../store/store.hpp"

#include <fstream>
#include <string>

void deserialize_store(Store& store, std::ifstream& fs);

void deserialize_seq_grid(Seq_Grid& seq_grid, std::ifstream& fs);

void deserialize_grid_cell(Grid_Cell& grid_cell, std::ifstream& fs);

void deserialize_row_metadata(Row_Metadata& row_meta, std::ifstream& fs);
