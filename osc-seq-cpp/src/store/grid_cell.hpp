#pragma once

#include "event_editor.hpp"

#include <string>
#include <vector>

enum Grid_Cell_Data_Options {
    Op_Int          = 0x01,
    Op_Targets      = 0x02,
    Op_Osc_Data     = 0x04
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
    std::vector<Target> targets;

    unsigned int options;

    Grid_Cell_Data();
    Grid_Cell_Data(std::string key, unsigned int options);
    Grid_Cell_Data(std::string key, int int_value, int min, int max, unsigned int options);
    std::string get_value_str();
    void increment();
    void decrement();
};

struct Grid_Cell
{
    bool toggled;
    bool has_meta;

    std::vector<Grid_Cell_Data> data;

    std::vector<Grid_Cell_Data> meta_data;

    Grid_Cell();
    Grid_Cell_Data& get_data(std::string key);
    Grid_Cell_Data& get_meta_data(std::string key);
    Grid_Cell_Data& get_selected(Event_Editor& event_editor);
};
