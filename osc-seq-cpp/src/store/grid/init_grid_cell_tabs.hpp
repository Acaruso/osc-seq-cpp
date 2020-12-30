#pragma once

#include "grid_cell_fields.hpp"
#include "tab.hpp"

std::vector<Tab> init_grid_cell_tabs();

Event_Field make_conditional_field(std::string key);

Event_Field make_mod_field(std::string key);

Dropdown_Entry get_dropdown_list(Options_Subfield& subfield, std::vector<Tab>& tabs);
