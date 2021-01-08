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

std::vector<Event_Field*> Grid_Cell::get_fields_by_flag(unsigned int flag)
{
    std::vector<Event_Field*> res;
    for (auto& tab : tabs) {
        for (auto& field : tab.fields) {
            if (field.flags & flag) {
                res.push_back(&field);
            }
        }
    }
    return res;
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
