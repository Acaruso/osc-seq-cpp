#pragma once

#include <string>
#include <vector>

struct Grid_Cell_Data
{
    std::string key;
    int value;
    int min;
    int max;
};

struct Target
{
    int row;
    int col;
};

struct Grid_Cell
{
    bool toggled;

    int probability;
    int retrigger;
    const static int num_fields = 2;

    std::vector<Grid_Cell_Data> data;

    bool has_meta;
    Target meta_target;
    const static int num_meta_fields = 1;

    Grid_Cell();
};
