#include "grid_cell_fields.hpp"

#include "../../util.hpp"

#include <iostream>

void Int_Subfield::update(Event_Editor& event_editor, int delta)
{
    data = clamp(data + delta, min, max);
}

void Int_Subfield::reset_meta_mods()
{
    meta_mod = 0;
}

std::string Int_Subfield::to_string()
{
    return std::to_string(data + meta_mod);
}

Event_Field make_conditional_field(std::string key) {
    return Event_Field{
        key,
        false,
        std::vector<Subfield>{
            Options_Subfield{
                "source1_type",
                1,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source1_const", 100, 0, 101, 0},
            Options_Subfield{
                "comp_type",
                1,
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
                0,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source2_const", 100, 0, 101, 0}
        }
    };
}

Event_Field make_mod_field(std::string key)
{
    return Event_Field{
        key,
        false,
        std::vector<Subfield>{
            Int_Pair_Subfield{
                "target",
                0, 0, 17, 0,
                0, 0, 17, 0
            },
            Options_Subfield{
                "mod dest",
                0,
                std::vector<std::string>{
                    "Cond1_Const1",
                    "Cond1_Const2",
                    "Cond2_Const1",
                    "Cond2_Const2",
                    "Retrigger",
                    "Note",
                    "Duration",
                    "Volume",
                    "Pan",
                    "Aux",
                    "Delay1",
                    "Delay2",
                    "Mod_Reg0",
                    "Mod_Reg1",
                }
            },
            Options_Subfield{
                "mod op",
                0,
                std::vector<std::string>{
                    "+=",
                    "-=",
                    "="
                }
            },
            Options_Subfield{
                "source type",
                0,
                std::vector<std::string>{
                    "Const",
                    "RNG",
                    "Reg0",
                    "Reg1"
                }
            },
            Int_Subfield{"source const", 0, 0, 101, 0}
        }
    };
}
