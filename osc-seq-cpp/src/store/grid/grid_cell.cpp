#include "grid_cell.hpp"

#include <iostream>

#include "../../util.hpp"
#include "init_grid_cell_tabs.hpp"

Grid_Cell::Grid_Cell(int channel) : Grid_Cell()
{
    this->channel = channel;
}

Grid_Cell::Grid_Cell()
: toggled(false)
{
    this->tabs = init_grid_cell_tabs();
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

Dropdown_Entry Grid_Cell::get_dropdown_list(Options_Subfield& subfield)
{
    if (subfield.key == "mod_dest") {
        Dropdown_Entry root_entry{"root"};
        for (auto& tab : tabs) {
            Dropdown_Entry tab_entry{tab.key};
            for (auto& field : tab.fields) {
                Dropdown_Entry field_entry{field.key};
                for (auto& subfield : field.subfields) {
                    if (can_be_mod_dest(subfield)) {
                        Dropdown_Entry subfield_entry{get_key(subfield)};
                        field_entry.subentries.push_back(subfield_entry);
                    }
                }
                tab_entry.subentries.push_back(field_entry);
            }
            root_entry.subentries.push_back(tab_entry);
        }
        Dropdown_Entry other{"other"};
        Dropdown_Entry regs{"regs"};
        regs.subentries.push_back(Dropdown_Entry{"$0"});
        regs.subentries.push_back(Dropdown_Entry{"$1"});
        other.subentries.push_back(regs);
        root_entry.subentries.push_back(other);
        return root_entry;
    } else {
        Dropdown_Entry options_entry{"root"};
        for (std::string option : subfield.options) {
            options_entry.subentries.push_back(Dropdown_Entry{option});
        }
        return options_entry;
    }
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
