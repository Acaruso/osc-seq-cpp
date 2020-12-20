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
    tabs.push_back({
        "conds",
        std::vector<Event_Field>{
            {
                "cond1",
                false,
                Conditional_Field{
                    RNG,
                    Int_Field{100, 0, 101, 0},
                    Const,
                    Int_Field{100, 0, 101, 0},
                    LT_Eq
                }
            },
            {
                "cond2",
                false,
                Conditional_Field{
                    RNG,
                    Int_Field{100, 0, 101, 0},
                    Const,
                    Int_Field{100, 0, 101, 0},
                    LT_Eq
                }
            }
        }
    });

    tabs.push_back({
        "other",
        std::vector<Event_Field>{
            {
                "retrigger",
                false,
                Int_Field{1, 1, 17, 0}
            },
            {
                "note",
                true,
                Int_Field{48, 0, 101, 0}
            },
            {
                "duration",
                true,
                Int_Field{100, 0, 1000, 0}
            },
            {
                "volume",
                true,
                Int_Field{100, 0, 101, 0}
            },
            {
                "pan",
                true,
                Int_Field{50, 0, 101, 0}
            },
            {
                "aux",
                true,
                Int_Field{50, 0, 101, 0}
            },
            {
                "delay",
                false,
                Int_Pair_Field{
                    Int_Field{0, 0, 17, 0},
                    Int_Field{2, 2, 17, 0}
                }
            },
            {
                "mod",
                false,
                Mod_Field{
                    Int_Pair_Field{
                        Int_Field{0, 0, 17, 0},
                        Int_Field{0, 0, 17, 0}
                    },
                    Retrigger,
                    Plus_Eq,
                    Const,
                    Int_Field{0, 0, 101, 0}
                }
            }
        }
    });
}

Event_Field& Grid_Cell::get_event_field(std::string key)
{
    for (auto& tab : tabs) {
        for (auto& field : tab.fields) {
            if (field.key == key) {
                return field;
            }
        }
    }
}

void Grid_Cell::for_each_field(std::function<void(Event_Field&)> fn)
{
    for (auto& tab : tabs) {
        for (auto& field : tab.fields) {
            fn(field);
        }
    }
}

void Grid_Cell::init_event_field(std::string key, Grid_Cell& default_cell)
{
    auto& field = get_event_field(key);
    auto& default_field = default_cell.get_event_field(key);
    field.value = default_field.value;
}

Event_Field& Grid_Cell::get_selected_event_field(Event_Editor& ee)
{
    return tabs[ee.selected_tab].fields[ee.selected_row];
}

Tab& Grid_Cell::get_selected_tab(Event_Editor& event_editor)
{
    return tabs[event_editor.selected_tab];
}

void Grid_Cell::reset_meta_mods()
{
    for_each_field([](Event_Field& field) {
        std::visit(
            [](auto& value) { value.reset_meta_mods(); },
            field.value
        );
    });
}

std::string Grid_Cell::serialize()
{
    std::ostringstream ss;
    ss << "toggled: " + std::to_string(toggled) + " ";
    ss << "channel: " + std::to_string(channel) + " ";
    for_each_field([&](Event_Field& field) {
        ss << field.key << ": " << field.get_value_str() << " ";
    });
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

    deserialize_int_field("retrigger", ss);
    deserialize_int_field("note", ss);
    deserialize_int_field("duration", ss);
    deserialize_int_field("volume", ss);
    deserialize_int_field("pan", ss);
    deserialize_int_field("aux", ss);
    deserialize_int_pair_field("delay", ss);
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
