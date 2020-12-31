#pragma once

#include "grid_cell_fields.hpp"

#include <string>
#include <vector>

struct Tab
{
    std::string key;
    std::vector<Event_Field> fields;
};
