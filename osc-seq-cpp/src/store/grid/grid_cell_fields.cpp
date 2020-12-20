#include "grid_cell_fields.hpp"

#include "../../util.hpp"

void Int_Field::update(Event_Editor& event_editor, int delta)
{
    data = clamp(data + delta, min, max);
}

void Int_Field::reset_meta_mods()
{
    meta_mod = 0;
}

void Int_Pair_Field::update(Event_Editor& event_editor, int delta)
{
    if (event_editor.selected_col == 0) {
        first.data = clamp(
            first.data + delta,
            first.min,
            first.max
        );
    } else if (event_editor.selected_col == 1) {
        second.data = clamp(
            second.data + delta,
            second.min,
            second.max
        );
    }
}

void Int_Pair_Field::reset_meta_mods()
{
    first.meta_mod = 0;
    second.meta_mod = 0;
}

void Conditional_Field::update(Event_Editor& event_editor, int delta)
{
    if (event_editor.selected_col == 0) {
        source1_type = static_cast<Source_Type>(
            clamp(
                source1_type + delta,
                0,
                Num_Source_Type
            )
        );
    } else if (event_editor.selected_col == 1) {
        if (source1_type == Const) {
            source1_const.data = clamp(
                source1_const.data + delta,
                source1_const.min,
                source1_const.max
            );
        }
    } else if (event_editor.selected_col == 2) {
        comp_type = static_cast<Comp_Type>(
            clamp(
                comp_type + delta,
                0,
                Num_Comp_Type
            )
        );
    } else if (event_editor.selected_col == 3) {
        source2_type = static_cast<Source_Type>(
            clamp(
                source2_type + delta,
                0,
                Num_Source_Type
            )
        );
    } else if (event_editor.selected_col == 4) {
        if (source2_type == Const) {
            source2_const.data = clamp(
                source2_const.data + delta,
                source2_const.min,
                source2_const.max
            );
        }
    }
}

void Conditional_Field::reset_meta_mods()
{
    source1_const.meta_mod = 0;
    source2_const.meta_mod = 0;
}

void Mod_Field::update(Event_Editor& event_editor, int delta)
{
    switch (event_editor.selected_col) {
        case 0: {
            mod_dest = static_cast<Mod_Dest>(
                clamp(
                    mod_dest + delta,
                    0,
                    Num_Mod_Dest
                )
            );
            break;
        }
        case 1: {
            mod_op = static_cast<Mod_Op>(
                clamp(
                    mod_op + delta,
                    0,
                    Num_Mod_Op
                )
            );
            break;
        }
        case 2: {
            source1_type = static_cast<Source_Type>(
                clamp(
                    source1_type + delta,
                    0,
                    Num_Source_Type
                )
            );
            break;
        }
        case 3: {
            source1_const.data = clamp(
                source1_const.data + delta,
                source1_const.min,
                source1_const.max
            );
            break;
        }
    }
}

void Mod_Field::reset_meta_mods()
{
    source1_const.meta_mod = 0;
}

std::string Int_Field::to_string()
{
    return std::to_string(data + meta_mod);
}

std::string Int_Pair_Field::to_string()
{
    return std::to_string(first.data + first.meta_mod)
        + "," + std::to_string(second.data + second.meta_mod);
}

std::string Conditional_Field::to_string()
{
    return "conditional";
}

std::string Mod_Field::to_string()
{
    return "mod field";
}

std::string Event_Field::get_value_str()
{
    // use std::visit when all variant types expose same interface, ie to_string()
    return std::visit(
        [](auto& value) { return value.to_string(); },
        value
    );
}

Value_Display_Res Event_Field::get_value_display_str()
{
    switch (value.index()) {
        case 0: {
            auto& x = std::get<Int_Field>(value);
            if (key == "retrigger") {
                return x.data == 1
                    ? Value_Display_Res{"OFF"}
                    : Value_Display_Res{std::to_string(x.data) + "x"};
            } else {
                return Value_Display_Res{std::to_string(x.data)};
            }
        }
        case 1: {
            auto& x = std::get<Int_Pair_Field>(value);
            Value_Display_Res res;
            if (key == "delay") {
                std::string text1 = std::to_string(x.first.data);
                std::string text2 = std::to_string(x.second.data);
                res.text = text1 + " / " + text2;
                res.underline_idxs.push_back({
                    0,
                    text1.size()
                });
                res.underline_idxs.push_back({
                    (text1 + " / ").size(),
                    (text1 + " / " + text2).size()
                });
                return res;
            } else {
                res.text = std::to_string(x.first.data)
                    + " " + std::to_string(x.second.data);
                return res;
            }
        }
        case 2: {
            auto& x = std::get<Conditional_Field>(value);
            Value_Display_Res res;
            std::string s0 = "if";
            std::string s1 = source_type_to_string(x.source1_type);
            std::string s2 = const_to_string(x.source1_type, x.source1_const);
            std::string s3 = comp_type_to_string(x.comp_type);
            std::string s4 = source_type_to_string(x.source2_type);
            std::string s5 = const_to_string(x.source2_type, x.source2_const);

            int begin = s0.size() + 1;
            int end = begin + s1.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            begin = end + 1;
            end = begin + s2.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            begin = end + 1;
            end = begin + s3.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            begin = end + 1;
            end = begin + s4.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            begin = end + 1;
            end = begin + s5.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            res.text = s0 + " " + s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5;

            return res;
        }
        case 3: {
            auto& x = std::get<Mod_Field>(value);
            Value_Display_Res res;
            std::string s1 = "[" + std::to_string(x.target.first.data)
                    + " , " + std::to_string(x.target.second.data) + "]";
            std::string s2 = mod_dest_to_string(x.mod_dest);
            std::string s3 = mod_op_to_string(x.mod_op);
            std::string s4 = source_type_to_string(x.source1_type);
            std::string s5 = const_to_string(x.source1_type, x.source1_const);

            int begin = s1.size() + 1;
            int end = begin + s2.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            begin = end + 1;
            end = begin + s3.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            begin = end + 1;
            end = begin + s4.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            begin = end + 1;
            end = begin + s5.size();

            res.underline_idxs.push_back({
                begin,
                end
            });

            res.text = s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5;

            return res;
        }
    }
}

std::string source_type_to_string(Source_Type type)
{
    switch (type) {
        case Const: {
            return "Const";
        }
        case RNG: {
            return "RNG";
        }
        case Reg0: {
            return "$0";
        }
        case Reg1: {
            return "$1";
        }
    }
}

std::string const_to_string(Source_Type type, Int_Field field)
{
    switch (type) {
        case Const: {
            return std::to_string(field.data);
        }
        default: {
            return "n/a";
        }
    }

}

std::string comp_type_to_string(Comp_Type type)
{
    switch (type) {
        case LT: {
            return "<";
        }
        case LT_Eq: {
            return "<=";
        }
        case GT: {
            return ">";
        }
        case GT_Eq: {
            return ">=";
        }
        case Eq: {
            return "==";
        }
    }
}

std::string mod_dest_to_string(Mod_Dest mod_dest)
{
    switch (mod_dest) {
        case Cond1_Const1: {
            return "Cond1 Const 1";
        }
        case Cond1_Const2: {
            return "Cond1 Const 2";
        }
        case Cond2_Const1: {
            return "Cond2 Const 1";
        }
        case Cond2_Const2: {
            return "Cond2 Const 2";
        }
        case Retrigger: {
            return "Retrigger";
        }
        case Note: {
            return "Note";
        }
        case Duration: {
            return "Duration";
        }
        case Volume: {
            return "Volume";
        }
        case Pan: {
            return "Pan";
        }
        case Aux: {
            return "Aux";
        }
        case Delay1: {
            return "Delay 1";
        }
        case Delay2: {
            return "Delay 2";
        }
        case Mod_Reg0: {
            return "$0";
        }
        case Mod_Reg1: {
            return "$1";
        }
    }
}

std::string mod_op_to_string(Mod_Op mod_op)
{
    switch (mod_op) {
        case Plus_Eq: {
            return "+=";
        }
        case Minus_Eq: {
            return "-=";
        }
        case Assn: {
            return "=";
        }
    }
}

void Event_Field::update(Event_Editor& event_editor, int delta)
{
    std::visit(
        [&](auto& value) { value.update(event_editor, delta); },
        value
    );
}

int Event_Field::get_num_subfields()
{
    return std::visit(
        [](auto& value) { return value.num_subfields; },
        value
    );
}
