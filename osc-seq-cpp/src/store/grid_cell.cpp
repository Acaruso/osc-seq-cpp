#include "grid_cell.hpp"

#include <iostream>

#include "../util.hpp"

Grid_Cell::Grid_Cell(int channel) : Grid_Cell()
{
    this->channel = channel;
}

Grid_Cell::Grid_Cell()
: toggled(false)
{
    fields.push_back({
        "probability",
        false,
        Int_Field{100, 0, 101, 10, 0}
    });

    fields.push_back({
        "retrigger",
        false,
        Int_Field{1, 1, 17, 1, 0}
    });

    fields.push_back({
        "note",
        true,
        Int_Field{48, 0, 101, 1, 0}
    });

    fields.push_back({
        "delay",
        false,
        Int_Pair_Field{
            Int_Field{0, 0, 17, 1, 0},
            Int_Field{2, 2, 17, 1, 0}
        }
    });

    meta_fields.push_back({
        "target",
        false,
        Int_Pair_Field{
            Int_Field{0, 0, 17, 1, 0},
            Int_Field{0, 0, 17, 1, 0}
        }
    });

    meta_fields.push_back({
        "probability mod",
        false,
        Int_Field{0, -100, 101, 10, 0}
    });
}

Event_Field& Grid_Cell::get_event_field(std::string key)
{
    for (auto& field : fields) {
        if (field.key == key) {
            return field;
        }
    }
    for (auto& field : meta_fields) {
        if (field.key == key) {
            return field;
        }
    }
}

std::string Event_Field::get_display_str(bool toggled)
{
    std::string value_str = toggled ? get_value_display_str() : "";
    return key + ": " + value_str;
}

std::string Event_Field::get_value_str()
{
    switch (value.index()) {
        case 0:
            auto x = std::get<Int_Field>(value);
            return std::to_string(x.data);
        case 1:
            return "Pair Value";
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
    }
}

void Event_Field::increment(Event_Editor& event_editor)
{
    switch (value.index()) {
    case 0: {
        auto& x = std::get<Int_Field>(value);
        x.data = clamp(x.data + x.delta, x.min, x.max);
        return;
    }
    case 1: {
        auto& x = std::get<Int_Pair_Field>(value);
        if (event_editor.selected_col == 0) {
            x.first.data = clamp(
                x.first.data + x.first.delta,
                x.first.min,
                x.first.max
            );
        } else if (event_editor.selected_col == 1) {
            x.second.data = clamp(
                x.second.data + x.second.delta,
                x.second.min,
                x.second.max
            );
        }
        return;
    }
    }
}

void Event_Field::decrement(Event_Editor& event_editor)
{
    switch (value.index()) {
    case 0: {
        auto& x = std::get<Int_Field>(value);
        x.data = clamp(x.data - x.delta, x.min, x.max);
        return;
    }
    case 1: {
        auto& x = std::get<Int_Pair_Field>(value);
        if (event_editor.selected_col == 0) {
            x.first.data = clamp(
                x.first.data - x.first.delta,
                x.first.min,
                x.first.max
            );
        } else if (event_editor.selected_col == 1) {
            x.second.data = clamp(
                x.second.data - x.second.delta,
                x.second.min,
                x.second.max
            );
        }
        return;
    }
    }
}

void Grid_Cell::init_event_field(std::string key)
{
    auto& field = get_event_field(key);
    if (key == "probability") {
        field.value = Int_Field{100, 0, 101};
    } else if (key == "retrigger") {
        field.value = Int_Field{1, 1, 17};
    } else if (key == "note") {
        field.value = Int_Field{48, 0, 101};
    } else if (key == "delay") {
        field.value = Int_Pair_Field{
            Int_Field{0, 0, 17},
            Int_Field{2, 2, 17}
        };
    } else if (key == "target") {
        field.value = Int_Pair_Field{
            Int_Field{0, 0, 17, 1, 0},
            Int_Field{0, 0, 17, 1, 0}
        };
    } else if (key == "probability mod") {
        field.value = Int_Field{0, -100, 101, 10, 0};
    }
}

Event_Field& Grid_Cell::get_selected_event(Event_Editor& event_editor)
{
    if (event_editor.selected_row < fields.size()) {
        return fields[event_editor.selected_row];
    } else {
        int idx = event_editor.selected_row - fields.size();
        return meta_fields[idx];
    }
}
