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

    template<typename T>
    T& get_subfield(std::string field_key, std::string subfield_key)
    {
        auto& field = get_event_field(field_key);

        auto get_key_v = [](auto& value) { return value.key; };
        for (auto& sf : field.subfields) {
            if (std::visit(get_key_v, sf) == key) {
                return std::get<T>(sf);
            }
        }
    }

    void for_each_field(std::function<void(Event_Field&)> fn);

    void for_each_subfield(std::function<void(Subfield&)> fn);

    void init_event_field(std::string key, Grid_Cell& default_cell);

    Event_Field& get_selected_event_field(Event_Editor& event_editor);

    Tab& get_selected_tab(Event_Editor& event_editor);

    void reset_meta_mods();

    std::vector<Subfield>& get_subfields(std::string key);
};
