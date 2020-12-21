#pragma once

#include "../event_editor.hpp"
#include "../register.hpp"

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
    std::vector<bool> has_dropdown{false};

    void update(Event_Editor& event_editor, int delta);
    void reset_meta_mods();
    std::string to_string();
};

struct Int_Pair_Field
{
    Int_Field first;
    Int_Field second;
    int num_subfields = 2;
    std::vector<bool> has_dropdown{false, false};

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
    Comp_Type comp_type;
    Source_Type source2_type;
    Int_Field source2_const;

    int num_subfields = 5;
    std::vector<bool> has_dropdown{true, false, true, true, false};

    void update(Event_Editor& event_editor, int delta);
    void reset_meta_mods();
    std::string to_string();
};

enum Mod_Dest
{
    Cond1_Const1,
    Cond1_Const2,
    Cond2_Const1,
    Cond2_Const2,
    Retrigger,
    Note,
    Duration,
    Volume,
    Pan,
    Aux,
    Delay1,
    Delay2,
    Mod_Reg0,
    Mod_Reg1,
    Num_Mod_Dest
};

enum Mod_Op
{
    Plus_Eq,
    Minus_Eq,
    Assn,
    Num_Mod_Op
};

struct Mod_Field
{
    Int_Pair_Field target;
    Mod_Dest mod_dest;
    Mod_Op mod_op;
    Source_Type source1_type;
    Int_Field source1_const;

    int num_subfields = 4;
    std::vector<bool> has_dropdown{true, true, true, true, false};

    void update(Event_Editor& event_editor, int delta);
    void reset_meta_mods();
    std::string to_string();
};

struct Value_Display_Res
{
    std::string text;
    std::vector<std::pair<int, int>> subfield_idxs;
};

struct Event_Field
{
    std::string key;
    bool is_osc_data;
    std::variant<Int_Field, Int_Pair_Field, Conditional_Field, Mod_Field> value;

    std::string get_value_str();
    Value_Display_Res get_value_display();
    int get_num_subfields();
    std::vector<bool>& get_has_dropdown();
    void update(Event_Editor& event_editor, int delta);
};

struct Tab
{
    std::string key;
    std::vector<Event_Field> fields;
};

std::string source_type_to_string(Source_Type type);
std::string const_to_string(Source_Type type, Int_Field field);
std::string comp_type_to_string(Comp_Type type);
std::string mod_dest_to_string(Mod_Dest mod_dest);
std::string mod_op_to_string(Mod_Op mod_op);
