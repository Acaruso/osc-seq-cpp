#include "serialize.hpp"

#include <iostream>
#include <sstream>

std::string serialize_store(Store& store)
{
    std::ostringstream ss;
    ss << store.bpm << std::endl;
    ss << serialize_seq_grid(store.seq_grid);
    return ss.str();
}

std::string serialize_seq_grid(Seq_Grid& seq_grid)
{
    std::ostringstream ss;

    ss << "PATTERN BANK" << std::endl;
    ss << seq_grid.num_patterns << std::endl;
    ss << seq_grid.pattern_bank[0].numRows << std::endl;
    ss << seq_grid.pattern_bank[0].numCols << std::endl;
    for (auto& pattern : seq_grid.pattern_bank) {
        for (auto& row : pattern.data) {
            for (auto& cell : row) {
                ss << serialize_grid_cell(cell);
                ss << std::endl;
            }
        }
    }

    ss << "ROW METADATA" << std::endl;
    ss << seq_grid.row_metadata.size() << std::endl;
    for (auto& row_meta : seq_grid.row_metadata) {
        ss << serialize_row_metadata(row_meta);
        ss << std::endl;
    }

    return ss.str();
}

std::string serialize_grid_cell(Grid_Cell& grid_cell)
{
    std::ostringstream ss;
    ss << grid_cell.toggled << ", ";
    ss << grid_cell.channel << ", ";
    for (auto& tab : grid_cell.tabs) {
        for (auto& field : tab.fields) {
            for (auto& subfield : field.subfields) {
                if (auto v = std::get_if<Int_Subfield>(&subfield)) {
                    ss << v->data << ", ";
                } else if (auto v = std::get_if<Options_Subfield>(&subfield)) {
                    ss << v->selected << ", ";
                    ss << v->subfield_path.tab_key << ", ";
                    ss << v->subfield_path.field_key << ", ";
                    ss << v->subfield_path.subfield_key << ", ";
                }
            }
        }
    }
    return ss.str();
}

std::string serialize_row_metadata(Row_Metadata& row_meta)
{
    std::ostringstream ss;
    ss << row_meta.mute << ", ";
    ss << std::endl;
    ss << serialize_grid_cell(row_meta.default_grid_cell);
    return ss.str();
}
