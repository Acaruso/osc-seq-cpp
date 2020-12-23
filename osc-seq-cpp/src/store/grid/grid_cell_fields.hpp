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
};

struct Options_Subfield
{
    std::string key;
    int selected;
    std::vector<std::string> options;
};

using Subfield = std::variant<Int_Subfield, Options_Subfield>;

struct Value_Display_Res
{
    std::string text;
    std::vector<std::pair<int, int>> subfield_idxs;
};

struct Event_Field
{
    std::string key;
    bool is_osc_data;
    std::vector<Subfield> subfields;
};

struct Tab
{
    std::string key;
    std::vector<Event_Field> fields;
};

Event_Field make_conditional_field(std::string key);
