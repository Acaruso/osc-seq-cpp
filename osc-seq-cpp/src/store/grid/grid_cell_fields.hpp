#pragma once

#include "../event_editor.hpp"

#include <string>
#include <variant>

struct Int_Field
{
    int data;
    int min;
    int max;
    int meta_mod;
};

struct Int_Pair_Field
{
    Int_Field first;
    Int_Field second;
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
    Source_Type source2_type;
    Comp_Type comp_type;
    Int_Field source1_const;
    Int_Field source2_const;

    std::string to_display_string();
};

struct Event_Field
{
    std::string key;
    bool is_osc_data;
    std::variant<Int_Field, Int_Pair_Field, Conditional_Field> value;

    std::string get_display_str(bool toggled);
    std::string get_value_str();
    std::string get_value_display_str();
    void increment(Event_Editor& event_editor, int delta);
    void decrement(Event_Editor& event_editor, int delta);
};
