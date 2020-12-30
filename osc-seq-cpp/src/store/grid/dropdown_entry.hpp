#pragma once

#include <string>
#include <vector>

struct Dropdown_Entry
{
    std::string key;
    std::vector<Dropdown_Entry> subentries;
};
