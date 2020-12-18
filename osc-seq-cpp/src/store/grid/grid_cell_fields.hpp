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
    void reset_meta_mods();
    std::string to_string();
};

struct Int_Pair_Field
{
    Int_Field first;
    Int_Field second;
    int num_subfields = 2;

    void update(Event_Editor& event_editor, int delta);
    void reset_meta_mods();
    std::string to_string();
};

enum Source_Type
{
    Const,
    RNG,
    Reg0,
    Reg1,
    Num_Source_Type
};

enum Comp_Type
{
    LT,     // <
    LT_Eq,  // <=
    GT,     // >
    GT_Eq,  // >=
    Eq,     // ==
    Num_Comp_Type
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
    void reset_meta_mods();
    std::string to_string();
};

enum Mod_Dest
{
    Cond_Const1,
    Cond_Const2,
    Retrigger,
    Note,
    Duration,
    Volume,
    Pan,
    Aux,
    Delay1,
    Delay2,
    Num_Mod_Dest
};

struct Mod_Field
{
    Int_Pair_Field target;
    Mod_Dest mod_dest;
    Source_Type source1_type;
    Int_Field source1_const;

    int num_subfields = 3;

    void update(Event_Editor& event_editor, int delta);
    void reset_meta_mods();
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
    std::variant<Int_Field, Int_Pair_Field, Conditional_Field, Mod_Field> value;

    std::string get_value_str();
    Value_Display_Res get_value_display_str();
    int get_num_subfields();
    void update(Event_Editor& event_editor, int delta);
};
