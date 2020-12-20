#pragma once

#include <fstream>
#include <string>

#include "grid_cell.hpp"

struct Row_Metadata
{
    bool mute;
    int rng = 0;
    Grid_Cell default_grid_cell;

    std::string serialize();
    void deserialize(std::ifstream& fs);
};
