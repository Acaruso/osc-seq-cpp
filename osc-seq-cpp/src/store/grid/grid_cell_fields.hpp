#pragma once

#include "../event_editor.hpp"
#include "../register.hpp"

#include <functional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

struct Display_Res
{
    std::string text;
    std::vector<std::pair<int, int>> subfield_idxs;
};

struct Int_Subfield
{
    std::string key;
    bool is_selectable;
    int data;
    int min;
    int max;
    int meta_mod;

    void update(int delta);
    void reset_meta_mods();
    std::string to_string();
    std::string get_display();
};

struct Options_Subfield
{
    std::string key;
    bool is_selectable;
    int selected;
    std::string selected_str;
    std::vector<std::string> options;

    void update(int delta);
    void reset_meta_mods();
    std::string to_string();
    std::string get_display();
    std::string get_selected_option();
};

using Subfield = std::variant<Int_Subfield, Options_Subfield>;

struct Event_Field
{
    std::string key;
    bool is_osc_data;
    std::vector<Subfield> subfields;

    Display_Res get_display();

    Subfield& get_selected_subfield(Event_Editor& ee);

    int get_num_selectable_subfields();

    std::string to_string();

    bool should_set_subfield_na(
        Subfield& subfield,
        std::string type_key,
        std::string const_key
    );

    template<typename T>
    T& get_subfield(std::string key)
    {
        auto get_key_v = [](auto& value) { return value.key; };
        for (auto& sf : subfields) {
            if (std::visit(get_key_v, sf) == key) {
                return std::get<T>(sf);
            }
        }
    }
};

bool has_dropdown(Subfield& subfield);

void update(Subfield& subfield, int delta);

std::string get_key(Subfield& subfield);
