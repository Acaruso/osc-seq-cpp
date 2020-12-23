#include "draw_system.hpp"

#include <SDL.h>

#include "../ui_elements/root_elt.hpp"
#include "../sdl/sdl_wrapper.hpp"

void draw_system(Store& store)
{
    root_elt(store);
    draw_from_queue(store.window_renderer);
    SDL_RenderPresent(store.window_renderer);
}
