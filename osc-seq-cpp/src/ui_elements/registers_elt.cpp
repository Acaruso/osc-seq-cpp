#include "registers_elt.hpp"

#include "../store/rect.hpp"
#include "rect_elt.hpp"
#include "text_elt.hpp"

#include <iostream>
#include <vector>

std::vector<Color> colors{
    Color{51, 255, 204, 255},
    Color{255, 204, 0, 255}
};

void registers_elt(Coord& coord, Store& store)
{
    for (int i = 0; i < store.registers.size(); ++i) {
        Coord reg_coord = { coord.x + (i * 120), coord.y };
        register_elt(store.registers[i], colors[i], reg_coord, store);
    }
}

void register_elt(Register& reg, Color& color, Coord& coord, Store& store)
{
    std::string str = reg.name + ": " + std::to_string(reg.value)
        + " %% " + std::to_string(reg.mod);

    Rect rect1{
        coord.x - 1,
        coord.y - 1,
        ((str.size() - 1) * store.font_width) + 2,
        14 + 2
    };
    Color color1{0, 0, 0, 255};
    rect_elt(rect1, color1, store);

    Rect rect2{
        coord.x,
        coord.y,
        (str.size() - 1) * store.font_width,
        14
    };
    rect_elt(rect2, color, store);

    text_elt(str, coord, store);
}
