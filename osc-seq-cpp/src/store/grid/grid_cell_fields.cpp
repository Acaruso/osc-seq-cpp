#include "grid_cell_fields.hpp"

#include "../../util.hpp"

std::string source_type_to_string(Source_Type type, Int_Field field);
std::string const_to_string(Source_Type type, Int_Field field);
std::string comp_type_to_string(Comp_Type type);

void Int_Field::update(Event_Editor& event_editor, int delta)
{
    data = clamp(data + delta, min, max);
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

void Conditional_Field::update(Event_Editor& event_editor, int delta)
{
    // TODO: write this fn
    return;
}

std::string Int_Field::to_string()
{
    return std::to_string(data);
}

std::string Int_Pair_Field::to_string()
{
    return std::to_string(first.data) + "," + std::to_string(second.data);
}

std::string Conditional_Field::to_string()
{
    return "conditional";
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
            if (key == "probability") {
                return Value_Display_Res{std::to_string(x.data) + "%%"};
            } else if (key == "retrigger") {
                return x.data == 1
                    ? Value_Display_Res{"OFF"}
                    : Value_Display_Res{std::to_string(x.data) + "x"};
            } else if (key == "probability mod") {
                if (x.data >= 0) {
                    return Value_Display_Res{"+" + std::to_string(x.data) + "%%"};
                } else if (x.data < 0) {
                    return Value_Display_Res{std::to_string(x.data) + "%%"};
                }
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
                    res.text.size() - text2.size(),
                    res.text.size()
                });
                return res;
            } else if (key == "target") {
                res.text = "[" + std::to_string(x.first.data)
                    + " , " + std::to_string(x.second.data) + "]";
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
            res.text = "if " + source_type_to_string(x.source1_type, x.source1_const);
            res.text += " " + const_to_string(x.source1_type, x.source1_const);
            res.text += " " + comp_type_to_string(x.comp_type);
            res.text += " " + source_type_to_string(x.source2_type, x.source2_const);
            res.text += " " + const_to_string(x.source2_type, x.source2_const);
            return res;
        }
    }
}

std::string source_type_to_string(Source_Type type, Int_Field field)
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
