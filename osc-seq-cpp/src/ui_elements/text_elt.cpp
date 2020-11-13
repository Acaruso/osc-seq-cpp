#include "text_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"

void text_elt(
    std::string id,
    std::string text,
    Coord& coord,
    Store& store,
    std::function<void()> on_click,
    std::function<void(int drag_amount)> on_drag
) {
    TTF_Font* font = store.fonts["dos"];
    SDL_Color black = { 0, 0, 0 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), black);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        store.window_renderer,
        surface
    );

    Rect rect(surface->w, surface->h, coord.x, coord.y);

    if (is_mousedown_inside_rect(rect, store.ui_state)) {
        store.ui_state.cur_elt_id = id;
    }

    if (store.ui_state.click && store.ui_state.cur_elt_id == id) {
        on_drag(store.ui_state.prev_drag_y - store.ui_state.drag_y);
    }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(store.window_renderer, texture, NULL, &sdl_rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
