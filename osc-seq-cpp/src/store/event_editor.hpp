#pragma once

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
};
