#include "grid_cell_fields.hpp"

#include "../../util.hpp"

std::string Event_Field::get_display_str(bool toggled)
{
    std::string value_str = toggled ? get_value_display_str() : "";
    return key + ": " + value_str;
}

std::string Event_Field::get_value_str()
{
    switch (value.index()) {
        case 0: {
            auto& x = std::get<Int_Field>(value);
            return std::to_string(x.data);
        }
        case 1: {
            auto& x = std::get<Int_Pair_Field>(value);
            return std::to_string(x.first.data) + "," + std::to_string(x.second.data);
        }
        case 2: {
            return "conditional";
        }
    }
}

std::string Event_Field::get_value_display_str()
{
    switch (value.index()) {
        case 0: {
            auto& x = std::get<Int_Field>(value);
            if (key == "probability") {
                return std::to_string(x.data) + "%%";
            } else if (key == "retrigger") {
                return x.data == 1
                    ? "OFF"
                    : std::to_string(x.data) + "x";
            } else if (key == "probability mod") {
                if (x.data >= 0) {
                    return "+" + std::to_string(x.data) + "%%";
                } else if (x.data < 0) {
                    return std::to_string(x.data) + "%%";
                }
            } else {
                return std::to_string(x.data);
            }
        }
        case 1: {
            auto& x = std::get<Int_Pair_Field>(value);
            if (key == "delay") {
                return std::to_string(x.first.data)
                    + " / " + std::to_string(x.second.data);
            } else if (key == "target") {
                return "[" + std::to_string(x.first.data)
                    + " , " + std::to_string(x.second.data) + "]";
            } else {
                return std::to_string(x.first.data)
                    + " " + std::to_string(x.second.data);
            }
        }
        case 2: {
            return "conditional";
        }
    }
}

void Event_Field::increment(Event_Editor& event_editor, int delta)
{
    switch (value.index()) {
        case 0: {
            auto& x = std::get<Int_Field>(value);
            x.data = clamp(x.data + delta, x.min, x.max);
            return;
        }
        case 1: {
            auto& x = std::get<Int_Pair_Field>(value);
            if (event_editor.selected_col == 0) {
                x.first.data = clamp(
                    x.first.data + delta,
                    x.first.min,
                    x.first.max
                );
            } else if (event_editor.selected_col == 1) {
                x.second.data = clamp(
                    x.second.data + delta,
                    x.second.min,
                    x.second.max
                );
            }
            return;
        }
        case 2: {
            return;
        }
    }
}

void Event_Field::decrement(Event_Editor& event_editor, int delta)
{
    switch (value.index()) {
        case 0: {
            auto& x = std::get<Int_Field>(value);
            x.data = clamp(x.data - delta, x.min, x.max);
            return;
        }
        case 1: {
            auto& x = std::get<Int_Pair_Field>(value);
            if (event_editor.selected_col == 0) {
                x.first.data = clamp(
                    x.first.data - delta,
                    x.first.min,
                    x.first.max
                );
            } else if (event_editor.selected_col == 1) {
                x.second.data = clamp(
                    x.second.data - delta,
                    x.second.min,
                    x.second.max
                );
            }
            return;
        }
        case 2: {
            return;
        }
    }
}
