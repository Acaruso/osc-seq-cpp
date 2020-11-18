#pragma once

#include <string>
#include <vector>

enum Grid_Cell_Data_Options {
    Op_Int      = 0x01,
    Op_Target   = 0x02,
    Op_Osc_Data = 0x04,
};

struct Target
{
    int row;
    int col;
    Target();
    Target(int row, int col);
};

struct Grid_Cell_Data
{
    std::string key;
    int int_value;
    int min;
    int max;
    Target target;
    unsigned int options;
    Grid_Cell_Data();
    Grid_Cell_Data(std::string key, int int_value, int min, int max, unsigned int options);
    std::string get_value_str();
    void increment();
    void decrement();
};

struct Grid_Cell
{
    bool toggled;

    // int probability;
    // int retrigger;
    // const static int num_fields = 2;

    std::vector<Grid_Cell_Data> data;

    bool has_meta;

    // Target meta_target;
    // const static int num_meta_fields = 1;

    std::vector<Grid_Cell_Data> meta_data;

    Grid_Cell();
    Grid_Cell_Data& get_data(std::string key);
};
