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
    if (key == "mod_dest") {
        return subfield_path.subfield_key;
    } else {
        return options[selected];
    }
}

auto get_display_v = [](auto& value) { return value.get_display(); };

Display_Res Event_Field::get_display()
{
    if (flags & Delay_Field) {
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
    } else if (flags & Cond_Field) {
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
    } else if (flags & Mod_Field) {
        Display_Res res;
        std::string text_with_key = key + ": ";
        int i = 0;
        std::string delay1 = std::visit(get_display_v, subfields[i++]);
        std::string delay2 = std::visit(get_display_v, subfields[i++]);
        res.text += "[" + delay1 + " , " + delay2 + "] ";
        text_with_key += "[" + delay1 + " , " + delay2 + "] ";
        for (; i < subfields.size(); ++i) {
            auto& sf = subfields[i];
            std::string sf_res = std::visit(get_display_v, sf);
            if (should_set_subfield_na(sf, "source1_type", "source1_const")) {
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

Subfield& Event_Field::get_selected_subfield(Event_Editor& ee)
{
    int i = 0;
    for (auto& sf : subfields) {
        if (get_flags(sf) & Is_Selectable) {
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
        if (get_flags(sf) & Is_Selectable) {
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

unsigned int get_flags(Subfield& subfield)
{
    return std::visit([](auto& v) { return v.flags; }, subfield);
}

bool has_dropdown(Subfield& subfield)
{
    return (std::get_if<Options_Subfield>(&subfield) != 0);
}

bool can_be_mod_dest(Subfield& subfield)
{
    return (get_flags(subfield) & Can_Be_Mod_Dest);
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
