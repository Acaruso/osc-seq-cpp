#include "piano_keys_elt.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "../image_elt.hpp"
#include "../text_elt.hpp"

void piano_keys_elt(
    Tab& notes_tab,
    Coord& coord,
    Store& store
) {
    Subfield_Path path{"notes", "note1", "note1_subfield"};
    int note_num = notes_tab.get_subfield<Int_Subfield>(path).data;

    image_elt(store.images["piano-keys"], coord, store);

    int n = note_num % 12;

    if (n == 0) {
        image_elt(store.images["piano-keys-c"], coord, store, 1);
    } else if (n == 1) {
        image_elt(store.images["piano-keys-c#"], coord, store, 1);
    } else if (n == 2) {
        image_elt(store.images["piano-keys-d"], coord, store, 1);
    } else if (n == 3) {
        image_elt(store.images["piano-keys-d#"], coord, store, 1);
    } else if (n == 4) {
        image_elt(store.images["piano-keys-e"], coord, store, 1);
    } else if (n == 5) {
        image_elt(store.images["piano-keys-f"], coord, store, 1);
    } else if (n == 6) {
        image_elt(store.images["piano-keys-f#"], coord, store, 1);
    } else if (n == 7) {
        image_elt(store.images["piano-keys-g"], coord, store, 1);
    } else if (n == 8) {
        image_elt(store.images["piano-keys-g#"], coord, store, 1);
    } else if (n == 9) {
        image_elt(store.images["piano-keys-a"], coord, store, 1);
    } else if (n == 10) {
        image_elt(store.images["piano-keys-a#"], coord, store, 1);
    } else if (n == 11) {
        image_elt(store.images["piano-keys-b"], coord, store, 1);
    }
}
