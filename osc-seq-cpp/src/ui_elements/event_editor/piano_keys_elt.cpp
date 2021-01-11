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
    image_elt(store.images["piano-keys"], coord, store);

    Subfield_Path num_path{"notes", "num_notes", "num_notes_subfield"};
    int num_notes = notes_tab.get_subfield<Int_Subfield>(num_path).data;

    if (num_notes >= 1) {
        Subfield_Path note_path{"notes", "note1", "note1_subfield"};
        int note_num = notes_tab.get_subfield<Int_Subfield>(note_path).data;
        selected_note_elt(note_num, coord, store);
    }
    if (num_notes >= 2) {
        Subfield_Path note_path{"notes", "note2", "note2_subfield"};
        int note_num = notes_tab.get_subfield<Int_Subfield>(note_path).data;
        selected_note_elt(note_num, coord, store);
    }
    if (num_notes >= 3) {
        Subfield_Path note_path{"notes", "note3", "note3_subfield"};
        int note_num = notes_tab.get_subfield<Int_Subfield>(note_path).data;
        selected_note_elt(note_num, coord, store);
    }
    if (num_notes >= 4) {
        Subfield_Path note_path{"notes", "note4", "note4_subfield"};
        int note_num = notes_tab.get_subfield<Int_Subfield>(note_path).data;
        selected_note_elt(note_num, coord, store);
    }
    if (num_notes >= 5) {
        Subfield_Path note_path{"notes", "note5", "note5_subfield"};
        int note_num = notes_tab.get_subfield<Int_Subfield>(note_path).data;
        selected_note_elt(note_num, coord, store);
    }
}

void selected_note_elt(
    int note_num,
    Coord& coord,
    Store& store
) {
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
