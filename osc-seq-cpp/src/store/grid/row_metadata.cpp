#include "row_metadata.hpp"

std::string Row_Metadata::serialize()
{
    std::ostringstream ss;
    ss << mute << std::endl;
    // ss << default_grid_cell.serialize();
    return ss.str();
}

void Row_Metadata::deserialize(std::ifstream& fs)
{
    std::string str;
    std::getline(fs, str);
    mute = atoi(str.c_str());
    // default_grid_cell.deserialize(fs);
}
