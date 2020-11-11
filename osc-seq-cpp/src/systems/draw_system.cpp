#include "draw_system.hpp"

#include <SDL.h>

#include "../ui_elements/root_elt.hpp"

void draw_system(Store& store) {
    root_elt(store);

    SDL_RenderPresent(store.window_renderer);
}
