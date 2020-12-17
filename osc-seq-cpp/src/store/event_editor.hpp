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
    Event_Editor_Mode mode;
    std::string to_string()
    {
        return "selected_row: " + std::to_string(selected_row) + " "
            + "selected_col: " + std::to_string(selected_col) + " "
            + (mode == Event_Editor_Mode::Normal
                ? "mode: Normal"
                : "mode: Set_Default_Values"
            );
    }
};
