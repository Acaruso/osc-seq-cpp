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
    tabs.push_back(
        Tab{
            "conds",
            std::vector<Event_Field>{
                make_conditional_field("cond1"),
                make_conditional_field("cond2")
            }
        }
    );

    tabs.push_back(
        Tab{
            "basic",
            std::vector<Event_Field>{
                Event_Field{
                    "retrigger",
                    false,
                    std::vector<Subfield>{
                        Int_Subfield{"retrigger_subfield", true, 1, 1, 17, 0}
                    }
                },
                Event_Field{
                    "note",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"note_subfield", true, 48, 0, 101, 0}
                    }
                },
                Event_Field{
                    "volume",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"volume_subfield", true, 100, 0, 101, 0}
                    }
                },
                Event_Field{
                    "pan",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"pan_subfield", true, 50, 0, 101, 0}
                    }
                },
                Event_Field{
                    "aux",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"aux_subfield", true, 50, 0, 101, 0}
                    }
                },
                Event_Field{
                    "delay",
                    false,
                    std::vector<Subfield>{
                        Int_Subfield{"delay_subfield1", true, 0, 0, 17, 0},
                        Int_Subfield{"delay_subfield2", true, 2, 2, 17, 0},
                    }
                },
                make_mod_field("mod")
            }
        }
    );

    tabs.push_back(
        Tab{
            "env1",
            std::vector<Event_Field>{
                Event_Field{
                    "attack1",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"attack_subfield", true, 0, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "hold1",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"hold_subfield", true, 100, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "release1",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"release_subfield", true, 0, 0, 1001, 0}
                    }
                }
            }
        }
    );

    tabs.push_back(
        Tab{
            "env2",
            std::vector<Event_Field>{
                Event_Field{
                    "attack2",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"attack_subfield", true, 0, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "hold2",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"hold_subfield", true, 100, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "release2",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"release_subfield", true, 0, 0, 1001, 0}
                    }
                }
            }
        }
    );

    tabs.push_back(
        Tab{
            "env3",
            std::vector<Event_Field>{
                Event_Field{
                    "attack3",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"attack_subfield", true, 0, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "hold3",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"hold_subfield", true, 100, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "release3",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"release_subfield", true, 0, 0, 1001, 0}
                    }
                }
            }
        }
    );
}

Tab& Grid_Cell::get_tab(std::string key)
{
    for (auto& tab : tabs) {
        if (tab.key == key) {
            return tab;
        }
    }
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

void Grid_Cell::for_each_subfield(std::function<void(Subfield&)> fn)
{
    for (auto& tab : tabs) {
        for (auto& field : tab.fields) {
            for (auto& subfield : field.subfields) {
                fn(subfield);
            }
        }
    }
}

void Grid_Cell::init_event_field(std::string key, Grid_Cell& default_cell)
{
    auto& field = get_event_field(key);
    auto& default_field = default_cell.get_event_field(key);
    for (int i = 0; i < field.subfields.size(); ++i) {
        field.subfields[i] = default_field.subfields[i];
    }
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
    for_each_subfield([](Subfield& sf) {
        std::visit(
            [](auto& value) { value.reset_meta_mods(); },
            sf
        );
    });
}

std::vector<Dropdown_Entry> Grid_Cell::get_dropdown_list(
    Options_Subfield& subfield
) {
    std::vector<Dropdown_Entry> level1;

    if (subfield.key == "mod_dest") {
        for (auto& tab : tabs) {
            std::vector<Dropdown_Entry> level2;
            for (auto& event_field : tab.fields) {
                level2.push_back(Dropdown_Entry{event_field.key});
            }
            level1.push_back(Dropdown_Entry{tab.key});
        }
    } else {
        for (std::string option : subfield.options) {
            level1.push_back(Dropdown_Entry{option});
        }
    }
    return level1;
}

// std::string Grid_Cell::serialize()
// {
//     std::ostringstream ss;
//     ss << "toggled: " + std::to_string(toggled) + " ";
//     ss << "channel: " + std::to_string(channel) + " ";
//     for_each_field([&](Event_Field& field) {
//         ss << field.key << ": " << field.get_value_str() << " ";
//     });
//     return ss.str();
// }

// void Grid_Cell::deserialize(std::ifstream& fs)
// {
//     std::string line;
//     std::getline(fs, line);
//     std::stringstream ss{line};
//     std::string token1;
//     std::string token2;

//     ss >> token1;
//     ss >> token2;
//     toggled = atoi(token2.c_str());

//     ss >> token1;
//     ss >> token2;
//     channel = atoi(token2.c_str());

//     deserialize_int_field("retrigger", ss);
//     deserialize_int_field("note", ss);
//     deserialize_int_field("volume", ss);
//     deserialize_int_field("pan", ss);
//     deserialize_int_field("aux", ss);
//     deserialize_int_pair_field("delay", ss);
// }

// void Grid_Cell::deserialize_int_field(std::string key, std::stringstream& ss)
// {
//     std::string token;
//     ss >> token;
//     ss >> token;
//     get_event_value<Int_Field>(key).data = atoi(token.c_str());
// }

// void Grid_Cell::deserialize_int_pair_field(std::string key, std::stringstream& ss)
// {
//     std::string token;
//     ss >> token;
//     ss >> token;

//     std::stringstream ss2{token};

//     std::string s1;
//     std::string s2;

//     std::getline(ss2, s1, ',');
//     std::getline(ss2, s2, ',');

//     auto& field = get_event_value<Int_Pair_Field>(key);

//     field.first.data = atoi(s1.c_str());
//     field.second.data = atoi(s2.c_str());
// }

// void Grid_Cell::deserialize_conditional_field(std::string key, std::stringstream& ss)
// {
//     std::string token;
//     ss >> token;
//     ss >> token;
// }

// void Grid_Cell::print()
// {
//     std::cout << serialize() << std::endl;
// }
