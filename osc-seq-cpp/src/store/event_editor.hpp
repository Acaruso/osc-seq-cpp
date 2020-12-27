#pragma once

#include <string>

enum class Event_Editor_Mode
{
    Normal,
    Set_Default_Values
};

struct Event_Editor
{
    int selected_row;
    int selected_col;

    int selected_dropdown_row;
    int selected_dropdown_col;

    int selected_tab;

    Event_Editor_Mode mode;

    std::string to_string()
    {
        return "selected_row: " + std::to_string(selected_row) + " "
            + "selected_col: " + std::to_string(selected_col) + " "
            + "selected_dropdown_row: " + std::to_string(selected_dropdown_row) + " "
            + "selected_dropdown_col: " + std::to_string(selected_dropdown_col) + " "
            + (mode == Event_Editor_Mode::Normal
                ? "mode: Normal"
                : "mode: Set_Default_Values"
            );
    }
};
