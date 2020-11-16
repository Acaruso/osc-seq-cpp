#pragma once

#include "../store/event_editor.hpp"
#include "../store/grid.hpp"
#include "../store/store.hpp"
#include "../store/ui_state.hpp"

void control_system(Store& store);

void control_grid_selection_system(
    Seq_Grid& seq_grid,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
);

void control_event_editor_system(
    Seq_Grid& seq_grid,
    Event_Editor& event_editor,
    Ui_State& ui_state
);
