#pragma once

#include "../event_editor.hpp"
#include "dropdown_entry.hpp"
#include "grid_cell_fields.hpp"
#include "tab.hpp"

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

    Tab& get_tab(std::string key);

    Event_Field& get_event_field(std::string key);

    std::vector<Event_Field*> get_fields_by_flag(unsigned int flag);

    template<typename T>
    T& get_subfield(std::string field_key, std::string subfield_key)
    {
        auto& field = get_event_field(field_key);

        auto get_key_v = [](auto& value) { return value.key; };
        for (auto& sf : field.subfields) {
            if (std::visit(get_key_v, sf) == subfield_key) {
                return std::get<T>(sf);
            }
        }
    }

    template<typename T>
    T& get_subfield(Subfield_Path path)
    {
        for (auto& tab : tabs) {
            if (path.tab_key == tab.key) {
                for (auto& field : tab.fields) {
                    if (path.field_key == field.key) {
                        for (auto& subfield : field.subfields) {
                            if (path.subfield_key == get_key(subfield)) {
                                return std::get<T>(subfield);
                            }
                        }
                    }
                }
            }
        }
    }

    void for_each_field(std::function<void(Event_Field&)> fn);

    void for_each_subfield(std::function<void(Subfield&)> fn);

    void init_event_field(std::string key, Grid_Cell& default_cell);

    Event_Field& get_selected_event_field(Event_Editor& event_editor);

    Tab& get_selected_tab(Event_Editor& event_editor);

    void reset_meta_mods();

    // std::string serialize();

    // void deserialize(std::ifstream& fs);

    // void deserialize_int_field(std::string key, std::stringstream& ss);

    // void deserialize_int_pair_field(std::string key, std::stringstream& ss);

    // void deserialize_conditional_field(std::string key, std::stringstream& ss);

    // void print();
};
