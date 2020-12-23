#pragma once

#include "../event_editor.hpp"
#include "../register.hpp"

#include <string>
#include <utility>
#include <variant>
#include <vector>

struct Int_Subfield
{
    std::string key;
    int data;
    int min;
    int max;
    int meta_mod;

    void update(Event_Editor& event_editor, int delta);
    void reset_meta_mods();
    std::string to_string();
    Display_Res get_display();
};

struct Int_Pair_Subfield
{
    std::string key;

    int first_data;
    int first_min;
    int first_max;
    int first_meta_mod;

    int second_data;
    int second_min;
    int second_max;
    int second_meta_mod;

    void update(Event_Editor& event_editor, int delta);
    void reset_meta_mods();
    std::string to_string();
    Display_Res get_display();
};

struct Options_Subfield
{
    std::string key;
    int selected;
    std::vector<std::string> options;

    void update(Event_Editor& event_editor, int delta);
    void reset_meta_mods();
    std::string to_string();
    Display_Res get_display();
};

using Subfield = std::variant<Int_Subfield, Int_Pair_Subfield, Options_Subfield>;

struct Display_Res
{
    std::string text;
    std::vector<std::pair<int, int>> subfield_idxs;
};

struct Event_Field
{
    std::string key;
    bool is_osc_data;
    std::vector<Subfield> subfields;

    Display_Res get_display();
};

struct Tab
{
    std::string key;
    std::vector<Event_Field> fields;
};

Event_Field make_conditional_field(std::string key);

Event_Field make_mod_field(std::string key);
