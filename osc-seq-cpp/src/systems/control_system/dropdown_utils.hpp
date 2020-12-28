#pragma once

#include "../../store/store.hpp"

void toggle_dropdown_mode(Store& store);

void increment_dropdown_row(Store& store);

void decrement_dropdown_row(Store& store);

void increment_dropdown_col(Store& store);

void decrement_dropdown_col(Store& store);

Dropdown_Entry& get_selected_dropdown_entry(
    Dropdown_Entry& dd_list,
    Event_Editor& ee
);
