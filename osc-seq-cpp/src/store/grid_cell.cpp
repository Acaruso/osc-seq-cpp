#include "grid_cell.hpp"

#include <iostream>

#include "../util.hpp"

Grid_Cell::Grid_Cell(int channel) : Grid_Cell()
{
    this->channel = channel;
}

Grid_Cell::Grid_Cell()
: toggled(false), has_meta(false)
{
    fields.push_back({
        "probability",
        false,
        Int_Field{100, 0, 101}
    });

    fields.push_back({
        "retrigger",
        false,
        Int_Field{1, 1, 17}
    });

    fields.push_back({
        "note",
        true,
        Int_Field{48, 0, 101}
    });

    fields.push_back({
        "delay",
        false,
        Int_Pair_Field{
            Int_Field{0, 0, 17},
            Int_Field{2, 2, 17}
        }
    });

    fields.push_back({
        "meta event",
        false,
        Meta_Event_Field{
            Target{0, 0}
        }
    });
}

Event_Field& Grid_Cell::get_event_field(std::string key)
{
    for (auto& field : fields) {
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
    case 2:
        return "Meta Event Value";
    }
}

std::string Event_Field::get_value_display_str()
{
    switch (value.index()) {
    case 0:
    {
        auto& x = std::get<Int_Field>(value);
        if (key == "probability") {
            return std::to_string(x.data) + "%%";
        } else if (key == "retrigger") {
            return x.data == 1
                ? "OFF"
                : std::to_string(x.data) + "x";
        } else {
            return std::to_string(x.data);
        }
    }
    case 1:
    {
        auto& x = std::get<Int_Pair_Field>(value);
        if (key == "delay") {
            return std::to_string(x.first.data)
                + " / " + std::to_string(x.second.data);
        }
    }
    case 2:
        return "Meta Event!";
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
    }
}
