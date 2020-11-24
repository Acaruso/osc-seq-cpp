#include "grid_cell.hpp"

#include <iostream>

#include "../util.hpp"

Delay::Delay() {};

Delay::Delay(
    int amount,
    int division,
    int amount_min,
    int amount_max,
    int division_min,
    int division_max
) : amount(amount), division(division), amount_min(amount_min), amount_max(amount_max),
    division_min(division_min), division_max(division_max) {}

Grid_Cell_Data::Grid_Cell_Data() {}

Grid_Cell_Data::Grid_Cell_Data(std::string key, unsigned int options)
: key(key), options(options) {}

Grid_Cell_Data::Grid_Cell_Data(std::string key, Delay delay, unsigned int options)
: key(key), delay(delay), options(options) {}

Grid_Cell_Data::Grid_Cell_Data(
    std::string key,
    int int_value,
    int min,
    int max,
    unsigned int options
) : key(key), int_value(int_value), min(min), max(max), options(options) {}

void Grid_Cell_Data::increment()
{
    if (options & Op_Int) {
        if (key == "probability") {
            int_value = clamp(int_value + 10, min, max);
        } else {
            int_value = clamp(int_value + 1, min, max);
        }
    }
}

void Grid_Cell_Data::decrement()
{
    if (options & Op_Int) {
        if (key == "probability") {
            int_value = clamp(int_value - 10, min, max);
        } else {
            int_value = clamp(int_value - 1, min, max);
        }
    }
}

std::string Grid_Cell_Data::get_value_str()
{
    if (options & Op_Int) {
        if (key == "probability") {
            return std::to_string(int_value) + "%";
        } else if (key == "retrigger") {
            return int_value == 1
                ? "OFF"
                : std::to_string(int_value) + "x";
        } else {
            return std::to_string(int_value);
        }
    } else if (options & Op_Delay) {
        return std::to_string(delay.amount) + " / " + std::to_string(delay.division);
    }
}

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



    data.push_back({ "probability", 100, 0, 101, Op_Int });
    data.push_back({ "retrigger", 1, 1, 17, Op_Int });

    data.push_back({
        "delay",
        { 0, 0, 0, 0, 0, 0 },
        Op_Delay
    });

    data.push_back({ "note", 48, 0, 101, Op_Int | Op_Osc_Data });

    meta_data.push_back({ "num targets", 0, 0, 10, Op_Int });

    // meta_data.push_back({ "targets", Op_Targets });

    // meta_target.row = -1;
    // meta_target.col = -1;
}

Grid_Cell_Data& Grid_Cell::get_data(std::string key)
{
    for (auto& row : data) {
        if (row.key == key) {
            return row;
        }
    }
}

Grid_Cell_Data& Grid_Cell::get_meta_data(std::string key)
{
    for (auto& row : meta_data) {
        if (row.key == key) {
            return row;
        }
    }
}

Grid_Cell_Data& Grid_Cell::get_selected(Event_Editor& event_editor)
{
    if (event_editor.selected_row < data.size()) {
        return data[event_editor.selected_row];
    } else if (event_editor.selected_row >= data.size()) {
        int idx = event_editor.selected_row - data.size();
        return meta_data[idx];
    }
}

Event_Field& Grid_Cell::get_event_field(std::string key)
{
    for (auto& field : fields) {
        if (field.key == key) {
            return field;
        }
    }
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
    case 0:
    {
        auto x = std::get<Int_Field>(value);
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
        auto x = std::get<Int_Pair_Field>(value);
        if (key == "delay") {
            return std::to_string(x.first.data)
                + " / " + std::to_string(x.second.data);
        }
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
    }
}
