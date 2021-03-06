#include "control_system.hpp"

#include <iostream>

#include "../../util.hpp"
#include "../../store/grid/grid_cell.hpp"
#include "dropdown_utils.hpp"

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
            store.ui_state,
            store.prev_ui_state,
            store
        );

        control_pattern_grid_system(
            store.pattern_grid,
            store.seq_grid,
            store.ui_state
        );

        control_transport_system(
            store.transport_mode,
            store.clock,
            store.registers,
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

    if (
        (ui_state.up || ui_state.down || ui_state.left || ui_state.right)
        && !ui_state.lshift
        && !ui_state.lctrl
    ) {
        if (ui_state.mode == Normal) {
            if (ui_state.up) {
                seq_grid.decrement_selected_row();
            }
            if (ui_state.down) {
                seq_grid.increment_selected_row();
            }
            if (ui_state.right) {
                seq_grid.increment_selected_col();
            }
            if (ui_state.left) {
                seq_grid.decrement_selected_col();
            }
        } else if (ui_state.mode == Target_Select) {
            if (ui_state.up) {
                seq_grid.decrement_selected_target_row(event_editor);
            }
            if (ui_state.down) {
                seq_grid.increment_selected_target_row(event_editor);
            }
            if (ui_state.right) {
                seq_grid.increment_selected_target_col(event_editor);
            }
            if (ui_state.left) {
                seq_grid.decrement_selected_target_col(event_editor);
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
    Ui_State& ui_state,
    Ui_State& prev_ui_state,
    Store& store
) {
    Grid_Cell& grid_cell = ee.mode == Event_Editor_Mode::Normal
        ? seq_grid.get_selected_cell()
        : seq_grid.get_default_grid_cell();     // edit default values mode

    auto& tab = grid_cell.get_selected_tab(ee);
    auto& fields = tab.fields;
    auto& field = grid_cell.get_selected_event_field(ee);
    auto& subfield = field.get_selected_subfield(ee);

    // move selector up or down
    if (ui_state.w || ui_state.s) {
        if ((field.flags & Mod_Field) && ui_state.mode == Target_Select) {
            return;
        }

        if (ui_state.mode == Dropdown) {
            if (ui_state.w) {
                decrement_dropdown_row(store);
            } else if (ui_state.s) {
                increment_dropdown_row(store);
            }
        } else {
            ee.selected_col = 0;
            if (ui_state.w) {
                // change tabs
                if (ui_state.lalt) {
                    ee.selected_row = 0;
                    ee.selected_col = 0;
                    ee.selected_tab = clamp(
                        ee.selected_tab - 4,
                        0,
                        grid_cell.tabs.size()
                    );
                } else if (ui_state.lshift) {
                    update(subfield, 1);
                } else if (ui_state.lctrl) {
                    update_chord(grid_cell, 1);
                } else {
                    decrement(ee.selected_row, 0, fields.size());
                }
            } else if (ui_state.s) {
                // change tabs
                if (ui_state.lalt) {
                    ee.selected_row = 0;
                    ee.selected_col = 0;
                    ee.selected_tab = clamp(
                        ee.selected_tab + 4,
                        0,
                        grid_cell.tabs.size()
                    );
                } else if (ui_state.lshift) {
                    update(subfield, -1);
                } else if (ui_state.lctrl) {
                    update_chord(grid_cell, -1);
                } else {
                    increment(ee.selected_row, 0, fields.size());
                }
            }
        }
    }

    // increment or decrement currently selected field
    else if (ui_state.a || ui_state.d) {
        if (ui_state.mode == Normal) {
            if (ui_state.a) {
                if (ui_state.lctrl) {
                    if (field.flags & Note_Field) {
                        update_chord(grid_cell, -12);
                    }
                } else if (ui_state.lalt) {
                    ee.selected_row = 0;
                    ee.selected_col = 0;
                    decrement(ee.selected_tab, 0, grid_cell.tabs.size());
                } else if (ui_state.lshift) {
                    if (field.flags & Note_Field) {
                        update(subfield, -12);
                    } else {
                        update(subfield, -10);
                    }
                } else {
                    decrement(ee.selected_col, 0, field.get_num_selectable_subfields());
                }
            } else if (ui_state.d) {
                if (ui_state.lctrl) {
                    if (field.flags & Note_Field) {
                        update_chord(grid_cell, 12);
                    }
                } else if (ui_state.lalt) {
                    ee.selected_row = 0;
                    ee.selected_col = 0;
                    increment(ee.selected_tab, 0, grid_cell.tabs.size());
                } else if (ui_state.lshift) {
                    if (field.flags & Note_Field) {
                        update(subfield, 12);
                    } else {
                        update(subfield, 10);
                    }
                } else {
                    increment(ee.selected_col, 0, field.get_num_selectable_subfields());
                }
            }
        } else if (ui_state.mode == Dropdown) {
            if (ui_state.a) {
                decrement_dropdown_col(store);
            } else if (ui_state.d) {
                increment_dropdown_col(store);
            }
        }
    }

    // enter / exit target mode
    if (ui_state.f) {
        if (field.flags & Mod_Field) {
            if (ui_state.mode == Normal) {
                ui_state.mode = Target_Select;
            } else {
                ui_state.mode = Normal;
            }
            auto& target_row = field.get_subfield<Int_Subfield>("target_row");
            auto& target_col = field.get_subfield<Int_Subfield>("target_col");
            seq_grid.selected_target_row = target_row.data;
            seq_grid.selected_target_col = target_col.data;
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
    std::vector<Register>& registers,
    Ui_State& ui_state
) {
    if (ui_state.lctrl && ui_state.space) {
        if (transport_mode == Pause) {
            for (auto& reg : registers) {
                reg.value = 0;
            }
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
    // if (store.ui_state.e && !store.ui_state.lshift) {
    //     store.seq_grid.clear_row();
    // }

    // rotate, shift
    if (store.ui_state.lshift && !store.ui_state.lctrl && store.ui_state.right) {
        store.seq_grid.rotate_row_right();
    } else if (store.ui_state.lshift && !store.ui_state.lctrl && store.ui_state.left) {
        store.seq_grid.rotate_row_left();
    } /*else if (!store.ui_state.lshift && store.ui_state.lctrl && store.ui_state.right) {
        store.seq_grid.shift_row_right();
    } else if (!store.ui_state.lshift && store.ui_state.lctrl && store.ui_state.left) {
        store.seq_grid.shift_row_left();
    }*/

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

    // dropdown mode
    else if (store.ui_state.c) {
        toggle_dropdown_mode(store);
    }

    // print debug info
    else if (store.ui_state.p) {
        // store.seq_grid.get_selected_cell().print();
        std::cout << store.event_editor.to_string() << std::endl;
    }
}

void update_chord(Grid_Cell& grid_cell, int delta)
{
    auto note_fields = grid_cell.get_fields_by_flag(Note_Field);
    for (auto f : note_fields) {
        auto& sf = f->subfields[0];
        update(sf, delta);
    }
}
