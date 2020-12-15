#include "grid_cell.hpp"

#include <iostream>

#include "../../util.hpp"

Grid_Cell::Grid_Cell(int channel) : Grid_Cell()
{
    this->channel = channel;
}

Grid_Cell::Grid_Cell()
: toggled(false)
{
    fields.push_back({
        "cond",
        false,
        Conditional_Field{
            Const,
            Int_Field{100, 0, 101, 0},
            Const,
            Int_Field{100, 0, 101, 0},
            Eq
        }
    });

    fields.push_back({
        "probability",
        false,
        Int_Field{100, 0, 101, 0}
    });

    fields.push_back({
        "retrigger",
        false,
        Int_Field{1, 1, 17, 0}
    });

    fields.push_back({
        "note",
        true,
        Int_Field{48, 0, 101, 0}
    });

    fields.push_back({
        "duration",
        true,
        Int_Field{100, 0, 1000, 0}
    });

    fields.push_back({
        "volume",
        true,
        Int_Field{100, 0, 101, 0}
    });

    fields.push_back({
        "pan",
        true,
        Int_Field{50, 0, 101, 0}
    });

    fields.push_back({
        "aux",
        true,
        Int_Field{50, 0, 101, 0}
    });

    fields.push_back({
        "delay",
        false,
        Int_Pair_Field{
            Int_Field{0, 0, 17, 0},
            Int_Field{2, 2, 17, 0}
        }
    });

    meta_fields.push_back({
        "target",
        false,
        Int_Pair_Field{
            Int_Field{0, 0, 17, 0},
            Int_Field{0, 0, 17, 0}
        }
    });

    meta_fields.push_back({
        "probability mod",
        false,
        Int_Field{0, -100, 101, 0}
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

void Grid_Cell::init_event_field(std::string key)
{
    auto& field = get_event_field(key);

    if (key == "cond") {
        field.value = Conditional_Field{
            Const,
            Int_Field{100, 0, 101, 0},
            Const,
            Int_Field{100, 0, 101, 0},
            Eq
        };
    } else if (key == "probability") {
        field.value = Int_Field{100, 0, 101, 0};
    } else if (key == "retrigger") {
        field.value = Int_Field{1, 1, 17, 0};
    } else if (key == "note") {
        field.value = Int_Field{48, 0, 101, 0};
    } else if (key == "delay") {
        field.value = Int_Pair_Field{
            Int_Field{0, 0, 17, 0},
            Int_Field{2, 2, 17, 0}
        };
    } else if (key == "target") {
        field.value = Int_Pair_Field{
            Int_Field{0, 0, 17, 0},
            Int_Field{0, 0, 17, 0}
        };
    } else if (key == "probability mod") {
        field.value = Int_Field{0, -100, 101, 0};
    }
}

Event_Field& Grid_Cell::get_selected_event_field(Event_Editor& event_editor)
{
    if (event_editor.selected_row < fields.size()) {
        return fields[event_editor.selected_row];
    } else {
        int idx = event_editor.selected_row - fields.size();
        return meta_fields[idx];
    }
}

std::string Grid_Cell::serialize()
{
    std::ostringstream ss;
    ss << "toggled: " + std::to_string(toggled) + " ";
    ss << "channel: " + std::to_string(channel) + " ";
    for (auto& field : fields) {
        ss << field.key << ": " << field.get_value_str() << " ";
    }
    for (auto& field : meta_fields) {
        ss << field.key << ": " << field.get_value_str() << " ";
    }
    return ss.str();
}

void Grid_Cell::deserialize(std::ifstream& fs)
{
    std::string line;
    std::getline(fs, line);
    std::stringstream ss{line};
    std::string token1;
    std::string token2;

    ss >> token1;
    ss >> token2;
    toggled = atoi(token2.c_str());

    ss >> token1;
    ss >> token2;
    channel = atoi(token2.c_str());

    deserialize_int_field("probability", ss);
    deserialize_int_field("retrigger", ss);
    deserialize_int_field("note", ss);
    deserialize_int_field("duration", ss);
    deserialize_int_field("volume", ss);
    deserialize_int_field("pan", ss);
    deserialize_int_field("aux", ss);

    deserialize_int_pair_field("delay", ss);
    deserialize_int_pair_field("target", ss);

    deserialize_int_field("probability mod", ss);
}

void Grid_Cell::deserialize_int_field(std::string key, std::stringstream& ss)
{
    std::string token;
    ss >> token;
    ss >> token;
    get_event_value<Int_Field>(key).data = atoi(token.c_str());
}

void Grid_Cell::deserialize_int_pair_field(std::string key, std::stringstream& ss)
{
    std::string token;
    ss >> token;
    ss >> token;

    std::stringstream ss2{token};

    std::string s1;
    std::string s2;

    std::getline(ss2, s1, ',');
    std::getline(ss2, s2, ',');

    auto& field = get_event_value<Int_Pair_Field>(key);

    field.first.data = atoi(s1.c_str());
    field.second.data = atoi(s2.c_str());
}

void Grid_Cell::deserialize_conditional_field(std::string key, std::stringstream& ss)
{
    std::string token;
    ss >> token;
    ss >> token;
}

void Grid_Cell::print()
{
    std::cout << serialize() << std::endl;
}
