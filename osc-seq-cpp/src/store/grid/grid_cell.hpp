#pragma once

#include "../event_editor.hpp"

#include <variant>
#include <vector>
#include <string>

struct Target
{
    int row;
    int col;
};

struct Meta_Event_Field
{
    Target target;
};

struct Int_Field
{
    int data;
    int min;
    int max;
    int delta;
    int meta_mod;
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

    std::string get_display_str(bool toggled);
    std::string get_value_str();
    std::string get_value_display_str();
    void increment(Event_Editor& event_editor);
    void decrement(Event_Editor& event_editor);
};

struct Grid_Cell
{
    bool toggled;
    int channel;

    std::vector<Event_Field> fields;
    std::vector<Event_Field> meta_fields;

    Grid_Cell();
    Grid_Cell(int channel);

    Event_Field& get_event_field(std::string key);

    void init_event_field(std::string key);

    void init_all_event_fields();

    Event_Field& get_selected_event_field(Event_Editor& event_editor);

    template<typename T>
    T& get_event_value(std::string key)
    {
        Event_Field& field = get_event_field(key);
        T& x = std::get<T>(field.value);
        return x;
    }
};
