#pragma once

#include "../event_editor.hpp"

#include <string>
#include <utility>
#include <variant>
#include <vector>

struct Int_Field
{
    int data;
    int min;
    int max;
    int meta_mod;
    int num_subfields = 1;

    void update(Event_Editor& event_editor, int delta);
    std::string to_string();
};

struct Int_Pair_Field
{
    Int_Field first;
    Int_Field second;
    int num_subfields = 2;

    void update(Event_Editor& event_editor, int delta);
    std::string to_string();
};

enum Source_Type
{
    Const,
    RNG,
    Reg0,
    Reg1
};

enum Comp_Type
{
    LT,     // <
    LT_Eq,  // <=
    GT,     // >
    GT_Eq,  // >=
    Eq      // ==
};

struct Conditional_Field
{
    Source_Type source1_type;
    Int_Field source1_const;
    Source_Type source2_type;
    Int_Field source2_const;
    Comp_Type comp_type;

    int num_subfields = 5;

    void update(Event_Editor& event_editor, int delta);
    std::string to_string();
};

struct Value_Display_Res
{
    std::string text;
    std::vector<std::pair<int, int>> underline_idxs;
};

struct Event_Field
{
    std::string key;
    bool is_osc_data;
    std::variant<Int_Field, Int_Pair_Field, Conditional_Field> value;

    std::string get_value_str();
    Value_Display_Res get_value_display_str();
    int get_num_subfields();
    void update(Event_Editor& event_editor, int delta);
};
