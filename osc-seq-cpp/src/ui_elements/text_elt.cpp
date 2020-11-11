#include "text_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"

void text_elt(
    std::string id,
    TTF_Font* font,
    std::string text,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click,
    std::function<void(int drag_amount)> on_drag
) {
    SDL_Color black = { 0, 0, 0 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), black);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window_renderer, surface);

    Rect rect(surface->w, surface->h, coord.x, coord.y);

    if (is_mousedown(rect, ui_state)) {
        ui_state.cur_elt_id = id;
    }

    if (ui_state.click && ui_state.cur_elt_id == id) {
        on_drag(ui_state.prev_drag_y - ui_state.drag_y);
    }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(window_renderer, texture, NULL, &sdl_rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
