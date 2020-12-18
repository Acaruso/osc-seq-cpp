#include "registers_elt.hpp"

#include "text_elt.hpp"

void registers_elt(Coord& coord, Store& store)
{
    for (int i = 0; i < store.registers.size(); ++i) {
        Coord c = { coord.x + (i * 120), coord.y };
        register_elt(store.registers[i], c, store);
    }
}

void register_elt(Register& reg, Coord& coord, Store& store)
{
    std::string str = reg.name + ": " + std::to_string(reg.value)
        + " %% " + std::to_string(reg.mod);

    text_elt(str, coord, store);
}
