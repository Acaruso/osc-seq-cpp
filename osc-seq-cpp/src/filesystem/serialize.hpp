#pragma once

#include "../store/grid/seq_grid.hpp"
#include "../store/grid/tab.hpp"
#include "../store/store.hpp"

#include <string>

std::string serialize_store(Store& store);

std::string serialize_seq_grid(Seq_Grid& seq_grid);

std::string serialize_grid_cell(Grid_Cell& grid_cell);

std::string serialize_row_metadata(Row_Metadata& row_meta);
