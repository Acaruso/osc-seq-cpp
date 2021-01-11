#pragma once

#include "grid_cell_fields.hpp"

#include <string>
#include <vector>

struct Tab
{
    std::string key;
    std::vector<Event_Field> fields;

    Event_Field& get_event_field(std::string key)
    {
        for (auto& field : fields) {
            if (field.key == key) {
                return field;
            }
        }
    }

    template<typename T>
    T& get_subfield(Subfield_Path path)
    {
        auto& field = get_event_field(path.field_key);
        for (auto& subfield : field.subfields) {
            if (path.subfield_key == get_key(subfield)) {
                return std::get<T>(subfield);
            }
        }
    }
};
