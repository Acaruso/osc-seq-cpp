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
            "other",
            std::vector<Event_Field>{
                Event_Field{
                    "retrigger",
                    false,
                    std::vector<Subfield>{
                        Int_Subfield{"retrigger subfield", 1, 1, 17, 0}
                    }
                },
                Event_Field{
                    "note",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"note subfield", 48, 0, 101, 0}
                    }
                },
                Event_Field{
                    "duration",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"duration subfield", 100, 0, 1000, 0}
                    }
                },
                Event_Field{
                    "volume",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"volume subfield", 100, 0, 101, 0}
                    }
                },
                Event_Field{
                    "pan",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"pan subfield", 50, 0, 101, 0}
                    }
                },
                Event_Field{
                    "aux",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"aux subfield", 50, 0, 101, 0}
                    }
                },
                Event_Field{
                    "delay",
                    false,
                    std::vector<Subfield>{
                        Int_Subfield{"delay subfield 1", 0, 0, 17, 0},
                        Int_Subfield{"delay subfield 2", 2, 2, 17, 0},
                    }
                },
                make_mod_field("mod")
            }
        }
    );
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

std::vector<Subfield>& Grid_Cell::get_subfields(std::string key)
{
    return get_event_field(key).subfields;
}
