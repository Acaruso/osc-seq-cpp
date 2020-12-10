#include "control_system.hpp"

#include <iostream>

#include "../util.hpp"
#include "../store/grid/grid_cell.hpp"

void control_system(Store& store)
{
    if (store.ui_state.keydown_event) {
        control_grid_selection_system(
            store.seq_grid,
            store.pattern_grid,
            store.event_editor,
            store.ui_state,
            store.prev_ui_state
        );

        control_event_editor_system(
            store.seq_grid,
            store.event_editor,
            store.ui_state
        );

        control_pattern_grid_system(
            store.pattern_grid,
            store.seq_grid,
            store.ui_state
        );

        control_transport_system(
            store.transport_mode,
            store.clock,
            store.ui_state
        );

        control_mutes_system(
            store.seq_grid,
            store.ui_state
        );

        handle_keyboard_commands(
            store
        );
    }
}

void control_grid_selection_system(
    Seq_Grid& seq_grid,
    Pattern_Grid& pattern_grid,
    Event_Editor& event_editor,
    Ui_State& ui_state,
    Ui_State& prev_ui_state
) {
    Grid_Cell& grid_cell = seq_grid.get_selected_cell();

    if (is_event(Event::Space, ui_state, prev_ui_state) && !ui_state.lctrl) {
        seq_grid.set_toggled(
            seq_grid.selected_row,
            seq_grid.selected_col,
            ui_state,
            event_editor
        );
        return;
    }

    if (is_event(Event::Tab, ui_state, prev_ui_state)) {
        event_editor.selected_col = (event_editor.selected_col + 1) % 2;
    }

    if (
        (ui_state.up || ui_state.down || ui_state.left || ui_state.right)
        && !ui_state.lshift
        && !ui_state.lctrl
    ) {
        if (ui_state.mode == Normal) {
            if (ui_state.up) {
                seq_grid.decrement_selected_row(event_editor);
            }
            if (ui_state.down) {
                seq_grid.increment_selected_row(event_editor);
            }
            if (ui_state.right) {
                seq_grid.increment_selected_col(event_editor);
            }
            if (ui_state.left) {
                seq_grid.decrement_selected_col(event_editor);
            }
        } else if (ui_state.mode == Target_Select) {
            if (ui_state.up) {
                seq_grid.decrement_selected_target_row();
            }
            if (ui_state.down) {
                seq_grid.increment_selected_target_row();
            }
            if (ui_state.right) {
                seq_grid.increment_selected_target_col();
            }
            if (ui_state.left) {
                seq_grid.decrement_selected_target_col();
            }
        } else if (ui_state.mode == Pattern_Copy) {
            if (ui_state.up) {
                pattern_grid.decrement_selected_copy_row();
            }
            if (ui_state.down) {
                pattern_grid.increment_selected_copy_row();
            }
            if (ui_state.left) {
                pattern_grid.decrement_selected_copy_col();
            }
            if (ui_state.right) {
                pattern_grid.increment_selected_copy_col();
            }
        }
    }
}

void control_event_editor_system(
    Seq_Grid& seq_grid,
    Event_Editor& ee,
    Ui_State& ui_state
) {
    if (ee.mode == Event_Editor_Mode::Normal) {
        Grid_Cell& grid_cell = seq_grid.get_selected_cell();

        if (!grid_cell.toggled) {
            return;
        }

        int len = grid_cell.fields.size() + grid_cell.meta_fields.size();

        // move selector up or down
        if (ui_state.w || ui_state.s) {
            if (ui_state.w) {
                decrement(ee.selected_row, 0, len);
            } else if (ui_state.s) {
                increment(ee.selected_row, 0, len);
            }

            auto& new_field = grid_cell.get_selected_event_field(ee);

            if (new_field.key == "target") {
                ui_state.mode = Target_Select;
                auto& target = grid_cell.get_event_value<Int_Pair_Field>("target");
                seq_grid.selected_target_row = target.first.data;
                seq_grid.selected_target_col = target.second.data;
            } else {
                ui_state.mode = Normal;
            }
        }

        // increment or decrement currently selected field
        auto& field = grid_cell.get_selected_event_field(ee);
        if (field.key != "target") {
            if (ui_state.a) {
                if (ui_state.lshift) {
                    field.decrement(ee, 10);
                } else {
                    field.decrement(ee, 1);
                }
            } else if (ui_state.d) {
                if (ui_state.lshift) {
                    field.increment(ee, 10);
                } else {
                    field.increment(ee, 1);
                }
            }
        }
    } else if (ee.mode == Event_Editor_Mode::Set_Default_Values) {
        Grid_Cell& grid_cell = seq_grid.get_default_grid_cell();

        int len = grid_cell.fields.size();

        // move selector up or down
        if (ui_state.w || ui_state.s) {
            if (ui_state.w) {
                decrement(ee.selected_row, 0, len);
            } else if (ui_state.s) {
                increment(ee.selected_row, 0, len);
            }
        }

        // increment or decrement currently selected field
        auto& field = grid_cell.get_selected_event_field(ee);
        if (ui_state.a) {
            if (ui_state.lshift) {
                field.decrement(ee, 10);
            } else {
                field.decrement(ee, 1);
            }
        } else if (ui_state.d) {
            if (ui_state.lshift) {
                field.increment(ee, 10);
            } else {
                field.increment(ee, 1);
            }
        }
    }
}

void control_pattern_grid_system(
    Pattern_Grid& pattern_grid,
    Seq_Grid& seq_grid,
    Ui_State& ui_state
) {
    if (
        (ui_state.up || ui_state.down || ui_state.left || ui_state.right)
        && ui_state.lctrl
        && ui_state.lshift
    ) {
        if (ui_state.mode == Normal) {
            if (ui_state.up) {
                pattern_grid.decrement_selected_row();
            }
            if (ui_state.down) {
                pattern_grid.increment_selected_row();
            }
            if (ui_state.left) {
                pattern_grid.decrement_selected_col();
            }
            if (ui_state.right) {
                pattern_grid.increment_selected_col();
            }
            seq_grid.set_selected_pattern(pattern_grid);
        } else if (ui_state.mode == Pattern_Copy) {
            if (ui_state.up) {
                pattern_grid.decrement_selected_copy_row();
            }
            if (ui_state.down) {
                pattern_grid.increment_selected_copy_row();
            }
            if (ui_state.left) {
                pattern_grid.decrement_selected_copy_col();
            }
            if (ui_state.right) {
                pattern_grid.increment_selected_copy_col();
            }
        }
    }
}

void control_transport_system(
    Transport_Mode& transport_mode,
    int& clock,
    Ui_State& ui_state
) {
    if (ui_state.lctrl && ui_state.space) {
        if (transport_mode == Pause) {
            clock = 0;
            transport_mode = Play;
        } else if (transport_mode == Play) {
            transport_mode = Pause;
        }
    }
}

void control_mutes_system(
    Seq_Grid& seq_grid,
    Ui_State& ui_state
) {
    if (ui_state.i1) {
        seq_grid.toggle_row_mute(0);
    } else if (ui_state.i2) {
        seq_grid.toggle_row_mute(1);
    } else if (ui_state.i3) {
        seq_grid.toggle_row_mute(2);
    } else if (ui_state.i4) {
        seq_grid.toggle_row_mute(3);
    } else if (ui_state.i5) {
        seq_grid.toggle_row_mute(4);
    } else if (ui_state.i6) {
        seq_grid.toggle_row_mute(5);
    }
}

void handle_keyboard_commands(
    Store& store
) {
    // clear row

    if (store.ui_state.e && !store.ui_state.lshift) {
        store.seq_grid.clear_row();
    }

    // rotate, shift

    else if (store.ui_state.lshift && !store.ui_state.lctrl && store.ui_state.right) {
        store.seq_grid.rotate_row_right();
    } else if (store.ui_state.lshift && !store.ui_state.lctrl && store.ui_state.left) {
        store.seq_grid.rotate_row_left();
    } else if (!store.ui_state.lshift && store.ui_state.lctrl && store.ui_state.right) {
        store.seq_grid.shift_row_right();
    } else if (!store.ui_state.lshift && store.ui_state.lctrl && store.ui_state.left) {
        store.seq_grid.shift_row_left();
    }

    // copy / paste pattern

    else if (
        store.ui_state.lctrl
        && store.ui_state.lshift
        && store.ui_state.c
        && store.ui_state.mode == Normal
    ) {
        store.copied_pattern = store.seq_grid.get_selected_pattern_copy();
        store.ui_state.mode = Pattern_Copy;
    } else if (
        store.ui_state.lctrl
        && store.ui_state.lshift
        && store.ui_state.v
        && store.ui_state.mode == Pattern_Copy
    ) {
        auto& pg = store.pattern_grid;
        int selected_pattern = (pg.selected_copy_row * pg.num_cols) + pg.selected_copy_col;

        store.seq_grid.pattern_bank[selected_pattern] = store.copied_pattern;

        store.pattern_grid.selected_copy_row = store.pattern_grid.selected_row;
        store.pattern_grid.selected_copy_col = store.pattern_grid.selected_col;

        store.ui_state.mode = Normal;
    }

    // set mode to Normal

    else if (store.ui_state.esc) {
        store.pattern_grid.selected_copy_row = store.pattern_grid.selected_row;
        store.pattern_grid.selected_copy_col = store.pattern_grid.selected_col;

        store.ui_state.mode = Normal;
    }

    // cut / copy / paste event
    else if (store.ui_state.lctrl && store.ui_state.x) {
        store.copied_cell = store.seq_grid.get_selected_cell_copy();
        Grid_Cell& gc = store.seq_grid.get_selected_cell();
        gc = Grid_Cell{gc.channel}; // init grid cell
    } else if (store.ui_state.lctrl && store.ui_state.c) {
        store.copied_cell = store.seq_grid.get_selected_cell_copy();
    } else if (store.ui_state.lctrl && store.ui_state.v) {
        store.seq_grid.get_selected_cell() = store.copied_cell;
    }

    // switch to default values mode in event editor

    else if (store.ui_state.r) {
        if (store.event_editor.mode == Event_Editor_Mode::Normal) {
            store.event_editor.mode = Event_Editor_Mode::Set_Default_Values;
        } else {
            store.event_editor.mode = Event_Editor_Mode::Normal;
        }
    }

    // print selected cell

    else if (store.ui_state.p) {
        store.seq_grid.get_selected_cell().print();
    }
}
