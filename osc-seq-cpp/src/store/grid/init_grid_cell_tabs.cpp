#include "init_grid_cell_tabs.hpp"

#include <vector>

std::vector<Tab> init_grid_cell_tabs()
{
    std::vector<Tab> tabs;

    tabs.push_back(
        Tab{
            "conds",
            std::vector<Event_Field>{
                make_conditional_field("cond1"),
                make_conditional_field("cond2")
            }
        }
    );

    tabs.push_back(
        Tab{
            "basic",
            std::vector<Event_Field>{
                Event_Field{
                    "retrigger",
                    false,
                    std::vector<Subfield>{
                        Int_Subfield{"retrigger_subfield", (Is_Selectable | Can_Be_Mod_Dest), 1, 1, 17, 0}
                    }
                },
                Event_Field{
                    "note",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"note_subfield", (Is_Selectable | Can_Be_Mod_Dest), 48, 0, 101, 0}
                    }
                },
                Event_Field{
                    "volume",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"volume_subfield", (Is_Selectable | Can_Be_Mod_Dest), 100, 0, 101, 0}
                    }
                },
                Event_Field{
                    "pan",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"pan_subfield", (Is_Selectable | Can_Be_Mod_Dest), 50, 0, 101, 0}
                    }
                },
                Event_Field{
                    "aux",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"aux_subfield", (Is_Selectable | Can_Be_Mod_Dest), 50, 0, 101, 0}
                    }
                },
                Event_Field{
                    "delay",
                    false,
                    std::vector<Subfield>{
                        Int_Subfield{"delay_subfield1", (Is_Selectable | Can_Be_Mod_Dest), 0, 0, 17, 0},
                        Int_Subfield{"delay_subfield2", (Is_Selectable | Can_Be_Mod_Dest), 2, 2, 17, 0},
                    }
                },
                make_mod_field("mod")
            }
        }
    );

    tabs.push_back(
        Tab{
            "env1",
            std::vector<Event_Field>{
                Event_Field{
                    "attack1",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"attack_subfield", (Is_Selectable | Can_Be_Mod_Dest), 0, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "hold1",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"hold_subfield", (Is_Selectable | Can_Be_Mod_Dest), 100, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "release1",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"release_subfield", (Is_Selectable | Can_Be_Mod_Dest), 0, 0, 1001, 0}
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
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"attack_subfield", (Is_Selectable | Can_Be_Mod_Dest), 0, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "hold2",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"hold_subfield", (Is_Selectable | Can_Be_Mod_Dest), 100, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "release2",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"release_subfield", (Is_Selectable | Can_Be_Mod_Dest), 0, 0, 1001, 0}
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
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"attack_subfield", (Is_Selectable | Can_Be_Mod_Dest), 0, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "hold3",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"hold_subfield", (Is_Selectable | Can_Be_Mod_Dest), 100, 0, 1001, 0}
                    }
                },
                Event_Field{
                    "release3",
                    true,
                    std::vector<Subfield>{
                        Int_Subfield{"release_subfield", (Is_Selectable | Can_Be_Mod_Dest), 0, 0, 1001, 0}
                    }
                }
            }
        }
    );

    return tabs;
}

Event_Field make_conditional_field(std::string key) {
    return Event_Field{
        key,
        false,
        std::vector<Subfield>{
            Options_Subfield{
                "source1_type",
                Is_Selectable,
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
                Is_Selectable,
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
                Is_Selectable,
                0,
                Subfield_Path{},
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "$0",
                    "$1"
                }
            },
            Int_Subfield{"source2_const", (Is_Selectable | Can_Be_Mod_Dest), 100, 0, 101, 0}
        }
    };
}

Event_Field make_mod_field(std::string key)
{
    return Event_Field{
        key,
        false,
        std::vector<Subfield>{
            Int_Subfield{"target_row", 0, 0, 0, 17, 0},
            Int_Subfield{"target_col", 0, 0, 0, 17, 0},
            Options_Subfield{
                "mod_dest",
                Is_Selectable,
                0,
                Subfield_Path{"conds", "cond1", "source2_const"},
                std::vector<std::string>{}
            },
            Options_Subfield{
                "mod_op",
                Is_Selectable,
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
                Is_Selectable,
                0,
                Subfield_Path{},
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "$0",
                    "$1"
                }
            },
            Int_Subfield{"source1_const", (Is_Selectable | Can_Be_Mod_Dest), 0, 0, 101, 0}
        }
    };
}
