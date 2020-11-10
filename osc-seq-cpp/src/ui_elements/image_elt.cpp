#include "image_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"

void image_elt(
    SDL_Texture* image,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    Rect rect;
    rect.x = coord.x;
    rect.y = coord.y;
    SDL_QueryTexture(image, NULL, NULL, &rect.w, &rect.h);

    if (is_mouseup(rect, ui_state)) {
        on_click();
    }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(window_renderer, image, NULL, &sdl_rect);
}
