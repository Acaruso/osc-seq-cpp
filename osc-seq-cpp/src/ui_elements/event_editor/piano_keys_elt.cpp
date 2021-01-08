#include "piano_keys_elt.hpp"

#include <string>
#include <vector>

#include "../image_elt.hpp"
#include "../text_elt.hpp"

void piano_keys_elt(
    Coord& coord,
    Store& store
) {
    image_elt(store.images["piano-keys"], coord, store);
}
