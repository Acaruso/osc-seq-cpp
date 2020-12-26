#include "grid_cell_fields.hpp"

#include "../../util.hpp"

#include <iostream>

void Int_Subfield::update(int delta)
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

std::string Int_Subfield::get_display()
{
    return std::to_string(data);
}

void Options_Subfield::update(int delta)
{
    selected = clamp(selected + delta, 0, options.size());
}

void Options_Subfield::reset_meta_mods()
{
}

std::string Options_Subfield::to_string()
{
    return "options subfield";
}

std::string Options_Subfield::get_display()
{
    return get_selected_option();
}

std::string Options_Subfield::get_selected_option()
{
    return options[selected];
}

auto get_display_v = [](auto& value) { return value.get_display(); };

Display_Res Event_Field::get_display()
{
    if (key == "delay") {
        Display_Res res;
        std::string text_with_key = key + ": (";
        std::string sf_res1 = std::visit(get_display_v, subfields[0]);
        std::string sf_res2 = std::visit(get_display_v, subfields[1]);

        res.subfield_idxs.push_back({
            text_with_key.size(),
            text_with_key.size() + sf_res1.size()
        });

        res.subfield_idxs.push_back({
            text_with_key.size() + sf_res1.size() + 3 /*" , "*/,
            text_with_key.size() + sf_res1.size() + 3 + sf_res2.size()
        });

        res.text = "(" + sf_res1 + " , " + sf_res2 + ")";
        return res;
    } else if (key == "cond1" || key == "cond2") {
        Display_Res res;
        std::string text_with_key = key + ": ";
        for (auto& sf : subfields) {
            std::string sf_res = std::visit(get_display_v, sf);

            if (should_set_subfield_na(sf, "source1_type", "source1_const")) {
                sf_res = "n/a";
            }

            if (should_set_subfield_na(sf, "source2_type", "source2_const")) {
                sf_res = "n/a";
            }

            res.subfield_idxs.push_back({
                text_with_key.size(),
                text_with_key.size() + sf_res.size(),
            });

            res.text += sf_res + " ";
            text_with_key += sf_res + " ";
        }
        return res;
    } else if (key == "mod") {
        Display_Res res;
        std::string text_with_key = key + ": ";
        for (auto& sf : subfields) {
            std::string sf_res = std::visit(get_display_v, sf);
            if (should_set_subfield_na(sf, "source1_type", "source1_const")) {
                sf_res = "n/a";
            }
            std::string key = get_key(sf);
            if (key != "target_row" && key != "target_col") {
                res.subfield_idxs.push_back({
                    text_with_key.size(),
                    text_with_key.size() + sf_res.size(),
                });
            }
            res.text += sf_res + " ";
            text_with_key += sf_res + " ";
        }
        return res;
    } else {
        Display_Res res;
        std::string text_with_key = key + ": ";
        for (auto& sf : subfields) {
            std::string sf_res = std::visit(get_display_v, sf);
            res.subfield_idxs.push_back({
                text_with_key.size(),
                text_with_key.size() + sf_res.size(),
            });
            res.text += sf_res + " ";
            text_with_key += sf_res + " ";
        }
        return res;
    }
}

bool Event_Field::should_set_subfield_na(
    Subfield& subfield,
    std::string type_key,
    std::string const_key
) {
    return (
        get_key(subfield) == const_key
        && get_subfield<Options_Subfield>(type_key)
            .get_selected_option() != "Const"
    );
}

auto get_selectable_v = [](auto& value) { return value.is_selectable; };

Subfield& Event_Field::get_selected_subfield(Event_Editor& ee)
{
    int i = 0;
    for (auto& sf : subfields) {
        if (std::visit(get_selectable_v, sf)) {
            if (i == ee.selected_col) {
                return sf;
            } else {
            ++i;
            }
        }
    }
}

int Event_Field::get_num_selectable_subfields()
{
    int res = 0;
    for (auto& sf : subfields) {
        if (std::visit(get_selectable_v, sf)) {
            ++res;
        }
    }
    return res;
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

bool has_dropdown(Subfield& subfield)
{
    return (std::get_if<Options_Subfield>(&subfield) != 0);
}

void update(Subfield& subfield, int delta)
{
    auto update_v = [&](auto& value) { value.update(delta); };
    std::visit(update_v, subfield);
}

std::string get_key(Subfield& subfield)
{
    auto get_key_v = [&](auto& value) { return value.key; };
    return std::visit(get_key_v, subfield);
}

Event_Field make_conditional_field(std::string key) {
    return Event_Field{
        key,
        false,
        std::vector<Subfield>{
            Options_Subfield{
                "source1_type",
                true,
                1,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source1_const", true, 100, 0, 101, 0},
            Options_Subfield{
                "comp_type",
                true,
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
                true,
                0,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source2_const", true, 100, 0, 101, 0}
        }
    };
}

Event_Field make_mod_field(std::string key)
{
    return Event_Field{
        key,
        false,
        std::vector<Subfield>{
            Int_Subfield{"target_row", false, 0, 0, 17, 0},
            Int_Subfield{"target_col", false, 0, 0, 17, 0},
            Options_Subfield{
                "mod_dest",
                true,
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
                true,
                0,
                std::vector<std::string>{
                    "+=",
                    "-=",
                    "="
                }
            },
            Options_Subfield{
                "source1_type",
                true,
                0,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source1_const", true, 0, 0, 101, 0}
        }
    };
}
