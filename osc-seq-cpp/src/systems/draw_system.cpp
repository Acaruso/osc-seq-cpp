#include "draw_system.hpp"
#include "../ui_elements/root_elt.hpp"
#include <SDL.h>

void draw_system(Store& store) {
    root_elt(store);

    SDL_RenderPresent(store.window_renderer);
}
