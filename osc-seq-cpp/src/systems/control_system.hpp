#pragma once

#include "../store/event_editor.hpp"
#include "../store/grid/grid.hpp"
#include "../store/grid/seq_grid.hpp"
#include "../store/store.hpp"
#include "../store/ui_state.hpp"

void control_system(Store& store);

void control_grid_selection_system(
    Seq_Grid& seq_grid,
    Pattern_Grid& pattern_grid,
    Event_Editor& event_editor,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
);

void control_event_editor_system(
    Seq_Grid& seq_grid,
    Event_Editor& event_editor,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
);

void control_pattern_grid_system(
    Pattern_Grid& pattern_grid,
    Seq_Grid& seq_grid,
    Ui_State& ui_state
);

void control_transport_system(
    Transport_Mode& transport_mode,
    int& clock,
    Ui_State& ui_state
);

void control_mutes_system(
    Seq_Grid& seq_grid,
    Ui_State& ui_state
);

void handle_keyboard_commands(
    Store& store
);
