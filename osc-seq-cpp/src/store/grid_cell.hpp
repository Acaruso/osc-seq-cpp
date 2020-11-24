#pragma once

#include "event_editor.hpp"

#include <string>
#include <variant>
#include <vector>

enum Grid_Cell_Data_Options {
    Op_Int          = 0x01,
    Op_Delay        = 0x02,
    Op_Meta_Event   = 0x04,
    Op_Osc_Data     = 0x08
};

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

struct Delay
{
    int amount;
    int division;
    int amount_min;
    int amount_max;
    int division_min;
    int division_max;
    Delay();
    Delay(
        int amount,
        int division,
        int amount_min,
        int amount_max,
        int division_min,
        int division_max
    );
};

struct Grid_Cell_Data
{
    std::string key;

    int int_value;
    int min;
    int max;
    Delay delay;
    Meta_Event meta_event;

    unsigned int options;

    Grid_Cell_Data();
    Grid_Cell_Data(std::string key, unsigned int options);
    Grid_Cell_Data(std::string key, Delay delay, unsigned int options);
    Grid_Cell_Data(std::string key, int int_value, int min, int max, unsigned int options);
    std::string get_value_str();
    void increment();
    void decrement();
};

struct Grid_Cell
{
    bool toggled;
    int channel;
    bool has_meta;

    std::vector<Event_Field> fields;

    std::vector<Grid_Cell_Data> data;

    std::vector<Grid_Cell_Data> meta_data;

    Grid_Cell();
    Grid_Cell(int channel);
    Grid_Cell_Data& get_data(std::string key);
    Grid_Cell_Data& get_meta_data(std::string key);
    Grid_Cell_Data& get_selected(Event_Editor& event_editor);

    Event_Field& get_event_field(std::string key);

    void init_event_field(std::string key);
};
