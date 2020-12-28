#pragma once

#include <string>
#include <vector>

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
    std::vector<int> selected_dropdown_rows;

    int selected_tab;

    Event_Editor_Mode mode;

    std::string to_string()
    {
        return "selected_row: " + std::to_string(selected_row) + "\n"
            + "selected_col: " + std::to_string(selected_col) + "\n"
            + "selected_dropdown_row: " + std::to_string(selected_dropdown_row) + "\n"
            + "selected_dropdown_col: " + std::to_string(selected_dropdown_col) + "\n"
            + dd_rows_to_string(selected_dropdown_rows)
            + (mode == Event_Editor_Mode::Normal
                ? "mode: Normal"
                : "mode: Set_Default_Values"
            ) + "\n\n";
    }

    std::string dd_rows_to_string(std::vector<int>& selected_dropdown_rows)
    {
        std::string out = "selected_dropdown_rows: \n";
        for (int i : selected_dropdown_rows) {
            out += std::to_string(i) + "\n";
        }
        return out;
    }
};
