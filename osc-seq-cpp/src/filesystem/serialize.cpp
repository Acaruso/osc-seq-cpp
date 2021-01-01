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
            }
        }
    }

    ss << "ROW METADATA" << std::endl;
    ss << seq_grid.row_metadata.size() << std::endl;
    for (auto& elt : seq_grid.row_metadata) {
        ss << elt.serialize() << std::endl;
    }

    return ss.str();
}

std::string serialize_grid_cell(Grid_Cell& grid_cell)
{
    std::ostringstream ss;
    ss << "{";
    ss << "toggled: " + std::to_string(grid_cell.toggled) + ", ";
    ss << "channel: " + std::to_string(grid_cell.channel) + ", ";
    ss << "tabs: [";
    for (auto& tab : grid_cell.tabs) {
        ss << serialize_tab(tab);
    }
    ss << "]";
    ss << "}";
    ss << std::endl;
    return ss.str();
}

std::string serialize_tab(Tab& tab)
{
    std::ostringstream ss;
    ss << "{";
    ss << "key: " + tab.key + ", ";
    ss << "fields: [";
    for (auto& field : tab.fields) {
        serialize_field(field);
    }
    ss << "]";
    ss << "}, ";
    return ss.str();
}

std::string serialize_field(Event_Field& field)
{
    std::ostringstream ss;
    ss << "{";
    ss << "key: " << field.key << ", ";
    ss << "flags: " << field.flags << ", ";
    ss << "subfields: [";
    for (auto& subfield : field.subfields) {
        serialize_subfield(subfield);
    }
    ss << "]";
    ss << "}";
    return ss.str();
}

std::string serialize_subfield(Subfield& subfield)
{
    std::ostringstream ss;
    ss << "{";
    ss << "type: ";
    if (std::get_if<Int_Subfield>(&subfield)) {
        ss << "Int_Subfield, ";
    } else if (std::get_if<Options_Subfield>(&subfield)) {
        ss << "Options_Subfield, ";
    }
    ss << "}";
    return ss.str();
}
