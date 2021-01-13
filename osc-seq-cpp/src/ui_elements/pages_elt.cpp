#include "pages_elt.hpp"

#include "text_elt.hpp"

#include <string>

void pages_elt(Coord& coord, Store& store)
{
    std::string str = "page: " + std::to_string(store.selected_page);
    text_elt(str, coord, store);
}
