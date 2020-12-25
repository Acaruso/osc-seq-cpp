#include "grid_cell_fields.hpp"

#include "../../util.hpp"

#include <iostream>

void Int_Subfield::update(Event_Editor& event_editor, int delta)
{
    data = clamp(data + delta, min, max);
}

void Int_Subfield::reset_meta_mods()
{
    meta_mod = 0;
}

std::string Int_Subfield::to_string()
{
    return std::to_string(data + meta_mod);
}

Display_Res Int_Subfield::get_display()
{
    Display_Res res;
    res.text = std::to_string(data);
    res.subfield_idxs.push_back({
        0,
        res.text.size()
    });
    return res;
}

void Int_Pair_Subfield::update(Event_Editor& event_editor, int delta)
{
    // TODO: fix this, it will only work if int pair subfield is first element in subfields vector
    // because event_editor.selected_col is "hardcoded" to 0 or 1 below
    if (event_editor.selected_col == 0) {
        first_data = clamp(
            first_data + delta,
            first_min,
            first_max
        );
    } else if (event_editor.selected_col == 1) {
        second_data = clamp(
            second_data + delta,
            second_min,
            second_max
        );
    }
}

void Int_Pair_Subfield::reset_meta_mods()
{
    first_meta_mod = 0;
    second_meta_mod = 0;
}

std::string Int_Pair_Subfield::to_string()
{
    return std::to_string(first_data + first_meta_mod)
        + "," + std::to_string(second_data + second_meta_mod);
}

Display_Res Int_Pair_Subfield::get_display()
{
    Display_Res res;
    std::string text1 = std::to_string(first_data);
    std::string text2 = std::to_string(second_data);
    res.text = "(" + text1 + " , " + text2 + ")";
    res.subfield_idxs.push_back({
        1,
        text1.size()
    });
    res.subfield_idxs.push_back({
        ("(" + text1 + " , ").size(),
        ("(" + text1 + " , " + text2).size()
    });
    return res;
}

void Options_Subfield::update(Event_Editor& event_editor, int delta)
{
    selected = clamp(selected + delta, 0, options.size());
}

void Options_Subfield::reset_meta_mods()
{
    // do nothing
}

std::string Options_Subfield::to_string()
{
    return "options subfield";
}

Display_Res Options_Subfield::get_display()
{
    Display_Res res;
    res.text = options[selected];

    // res.subfield_idxs.push_back({
    //     (key + ": ").size(),
    //     (key + ": ").size() + res.text.size()
    // });

    res.subfield_idxs.push_back({
        0,
        res.text.size()
    });

    return res;
}

std::string Options_Subfield::get_selected_option()
{
    return options[selected];
}

auto get_display_v = [](auto& value) { return value.get_display(); };

Display_Res Event_Field::get_display()
{
    Display_Res res{""};
    std::string text_with_key = key + ": ";
    for (auto& sf : subfields) {
        auto sf_res = std::visit(get_display_v, sf);
        for (auto& sf_idxs : sf_res.subfield_idxs) {
            res.subfield_idxs.push_back({
                sf_idxs.first + text_with_key.size(),
                sf_idxs.second + text_with_key.size(),
            });
        }
        res.text += sf_res.text + " ";
        text_with_key += sf_res.text + " ";
    }
    return res;
}

Subfield& Event_Field::get_selected_subfield(Event_Editor& ee)
{
    return subfields[ee.selected_col];
}

auto to_string_v = [](auto& value) { return value.to_string(); };

std::string Event_Field::to_string()
{
    std::string res = "";
    for (auto& sf : subfields) {
        res += std::visit(to_string_v, sf) + " ";
    }
    return res;
}

Event_Field make_conditional_field(std::string key) {
    return Event_Field{
        key,
        false,
        std::vector<Subfield>{
            Options_Subfield{
                "source1_type",
                1,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source1_const", 100, 0, 101, 0},
            Options_Subfield{
                "comp_type",
                1,
                std::vector<std::string>{
                    "<",
                    "<=",
                    ">",
                    ">=",
                    "=="
                }
            },
            Options_Subfield{
                "source2_type",
                0,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source2_const", 100, 0, 101, 0}
        }
    };
}

Event_Field make_mod_field(std::string key)
{
    return Event_Field{
        key,
        false,
        std::vector<Subfield>{
            Int_Pair_Subfield{
                "target",
                0, 0, 17, 0,
                0, 0, 17, 0
            },
            Options_Subfield{
                "mod_dest",
                0,
                std::vector<std::string>{
                    "Cond1_Const1",
                    "Cond1_Const2",
                    "Cond2_Const1",
                    "Cond2_Const2",
                    "Retrigger",
                    "Note",
                    "Duration",
                    "Volume",
                    "Pan",
                    "Aux",
                    "Delay1",
                    "Delay2",
                    "Mod_Reg0",
                    "Mod_Reg1",
                }
            },
            Options_Subfield{
                "mod_op",
                0,
                std::vector<std::string>{
                    "+=",
                    "-=",
                    "="
                }
            },
            Options_Subfield{
                "source1_type",
                0,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source1_const", 0, 0, 101, 0}
        }
    };
}
