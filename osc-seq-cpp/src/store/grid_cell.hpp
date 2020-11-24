#pragma once

#include "event_editor.hpp"

#include <string>
#include <variant>
#include <vector>

struct Target
{
    int row;
    int col;
};

struct Meta_Event
{
    Target target;
};

struct Int_Field
{
    int data;
    int min;
    int max;
};

struct Int_Pair_Field
{
    Int_Field first;
    Int_Field second;
};

struct Event_Field
{
    std::string key;
    bool is_osc_data;
    std::variant<Int_Field, Int_Pair_Field> value;
    std::string get_value_str();
    std::string get_value_display_str();
};

struct Grid_Cell
{
    bool toggled;
    int channel;
    bool has_meta;

    std::vector<Event_Field> fields;

    Grid_Cell();
    Grid_Cell(int channel);

    Event_Field& get_event_field(std::string key);
    void init_event_field(std::string key);
};
