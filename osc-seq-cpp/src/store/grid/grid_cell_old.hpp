#pragma once

#include "../event_editor.hpp"
#include "grid_cell_fields.hpp"

#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

struct Grid_Cell
{
    bool toggled;
    int channel;

    std::vector<Tab> tabs;

    Grid_Cell();
    Grid_Cell(int channel);

    Event_Field& get_event_field(std::string key);

    void for_each_field(std::function<void(Event_Field&)> fn);

    void init_event_field(std::string key, Grid_Cell& default_cell);

    Event_Field& get_selected_event_field(Event_Editor& event_editor);

    Tab& get_selected_tab(Event_Editor& event_editor);

    void reset_meta_mods();

    template<typename T>
    T& get_event_value(std::string key)
    {
        Event_Field& field = get_event_field(key);
        T& x = std::get<T>(field.value);
        return x;
    }

    std::string serialize();

    void deserialize(std::ifstream& fs);

    void deserialize_int_field(std::string key, std::stringstream& ss);

    void deserialize_int_pair_field(std::string key, std::stringstream& ss);

    void deserialize_conditional_field(std::string key, std::stringstream& ss);

    void print();
};
