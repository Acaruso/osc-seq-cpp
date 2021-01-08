#include "init_grid_cell_tabs.hpp"

#include <vector>

std::vector<Tab> init_grid_cell_tabs()
{
    std::vector<Tab> tabs;

    tabs.push_back(
        Tab{
            "basic",
            std::vector<Event_Field>{
                Event_Field{
                    "retrigger",
                    0,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "retrigger_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            1, 1, 17, 0
                        }
                    }
                },
                Event_Field{
                    "volume",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "volume_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            100, 0, 101, 0
                        }
                    }
                },
                Event_Field{
                    "pan",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "pan_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            50, 0, 101, 0
                        }
                    }
                },
                Event_Field{
                    "delay",
                    Delay_Field,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "delay_subfield1",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 17, 0
                        },
                        Int_Subfield{
                            "delay_subfield2",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            2, 2, 17, 0
                        },
                    }
                },
            }
        }
    );

    tabs.push_back(
        Tab{
            "notes",
            std::vector<Event_Field>{
                Event_Field{
                    "note",
                    Is_Osc_Data | Note_Field,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "note_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            48, 0, 101, 0
                        }
                    }
                }
            }
        }
    );

    tabs.push_back(
        Tab{
            "conds",
            std::vector<Event_Field>{
                Event_Field{
                    "should_trigger",
                    0,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "should_trigger_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            1, 0, 2, 0
                        }
                    }
                },
                make_conditional_field("cond1"),
                make_conditional_field("cond2"),
                make_conditional_field("cond3"),
                make_conditional_field("cond4"),
            }
        }
    );

    tabs.push_back(
        Tab{
            "mod",
            std::vector<Event_Field>{
                make_mod_field("mod1"),
                make_mod_field("mod2"),
                make_mod_field("mod3"),
                make_mod_field("mod4"),
            }
        }
    );

    tabs.push_back(
        Tab{
            "env1",
            std::vector<Event_Field>{
                Event_Field{
                    "attack1",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "attack_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "hold1",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "hold_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            100, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "release1",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "release_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                }
            }
        }
    );

    tabs.push_back(
        Tab{
            "env2",
            std::vector<Event_Field>{
                Event_Field{
                    "attack2",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "attack_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "hold2",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "hold_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            100, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "release2",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "release_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                }
            }
        }
    );

    tabs.push_back(
        Tab{
            "env3",
            std::vector<Event_Field>{
                Event_Field{
                    "attack3",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "attack_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "hold3",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "hold_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            100, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "release3",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "release_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                }
            }
        }
    );

    tabs.push_back(
        Tab{
            "aux",
            std::vector<Event_Field>{
                Event_Field{
                    "aux1",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "aux1_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "aux2",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "aux2_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "aux3",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "aux3_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "aux4",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "aux4_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "aux5",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "aux5_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "aux6",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "aux6_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "aux7",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "aux7_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
                Event_Field{
                    "aux8",
                    Is_Osc_Data,
                    std::vector<Subfield>{
                        Int_Subfield{
                            "aux8_subfield",
                            (Is_Selectable | Can_Be_Mod_Dest),
                            0, 0, 1001, 0
                        }
                    }
                },
            }
        }
    );

    for (auto& tab : tabs) {
        for (auto& field: tab.fields) {
            for (auto& subfield : field.subfields) {
                if (auto v = std::get_if<Options_Subfield>(&subfield)) {
                    v->dropdown_list = get_dropdown_list(
                        std::get<Options_Subfield>(subfield),
                        tabs
                    );
                }
            }
        }
    }

    return tabs;
}

Event_Field make_conditional_field(std::string key) {
    return Event_Field{
        key,
        Cond_Field,
        std::vector<Subfield>{
            Options_Subfield{
                "source1_type",
                (Is_Selectable),
                1,
                Subfield_Path{},
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "$0",
                    "$1"
                }
            },
            Int_Subfield{"source1_const", (Is_Selectable | Can_Be_Mod_Dest), 100, 0, 101, 0},
            Options_Subfield{
                "comp_type",
                (Is_Selectable),
                1,
                Subfield_Path{},
                std::vector<std::string>{
                    "<",
                    "<=",
                    ">",
                    ">=",
                    "=="
                }
            },
            Options_Subfield{
                "source2_type",
                (Is_Selectable),
                0,
                Subfield_Path{},
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "$0",
                    "$1"
                }
            },
            Int_Subfield{
                "source2_const",
                (Is_Selectable | Can_Be_Mod_Dest),
                100, 0, 101, 0
            }
        }
    };
}

Event_Field make_mod_field(std::string key)
{
    return Event_Field{
        key,
        Mod_Field,
        std::vector<Subfield>{
            Int_Subfield{
                "target_row",
                0,
                0, 0, 17, 0
            },
            Int_Subfield{
                "target_col",
                0,
                0, 0, 17, 0
            },
            Options_Subfield{
                "mod_dest",
                (Is_Selectable),
                0,
                Subfield_Path{"conds", "cond1", "source2_const"},
                std::vector<std::string>{}
            },
            Options_Subfield{
                "mod_op",
                (Is_Selectable),
                0,
                Subfield_Path{},
                std::vector<std::string>{
                    "+=",
                    "-=",
                    "="
                }
            },
            Options_Subfield{
                "source1_type",
                (Is_Selectable),
                0,
                Subfield_Path{},
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "$0",
                    "$1"
                }
            },
            Int_Subfield{
                "source1_const",
                (Is_Selectable | Can_Be_Mod_Dest),
                0, 0, 101, 0
            }
        }
    };
}

Dropdown_Entry get_dropdown_list(Options_Subfield& subfield, std::vector<Tab>& tabs)
{
    if (subfield.key == "mod_dest") {
        Dropdown_Entry root_entry{"root"};
        for (auto& tab : tabs) {
            Dropdown_Entry tab_entry{tab.key};
            for (auto& field : tab.fields) {
                Dropdown_Entry field_entry{field.key};
                for (auto& subfield : field.subfields) {
                    if (can_be_mod_dest(subfield)) {
                        Dropdown_Entry subfield_entry{get_key(subfield)};
                        field_entry.subentries.push_back(subfield_entry);
                    }
                }
                tab_entry.subentries.push_back(field_entry);
            }
            root_entry.subentries.push_back(tab_entry);
        }
        Dropdown_Entry other{"other"};
        Dropdown_Entry regs{"regs"};
        regs.subentries.push_back(Dropdown_Entry{"$0"});
        regs.subentries.push_back(Dropdown_Entry{"$1"});
        other.subentries.push_back(regs);
        root_entry.subentries.push_back(other);

        return root_entry;
    } else {
        Dropdown_Entry options_entry{"root"};
        for (std::string option : subfield.options) {
            options_entry.subentries.push_back(Dropdown_Entry{option});
        }
        return options_entry;
    }
}
