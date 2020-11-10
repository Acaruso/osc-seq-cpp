#include "text_elt.hpp"

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"

void text_elt(
    TTF_Font* font,
    std::string text,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click,
    std::function<void()> on_drag
) {
    SDL_Color black = { 0, 0, 0 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), black);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window_renderer, surface);

    Rect rect;
    rect.x = coord.x;
    rect.y = coord.y;
    rect.w = surface->w;
    rect.h = surface->h;

    // if (is_clicked(rect, ui_state)) {
    //     on_click();
    // }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(window_renderer, texture, NULL, &sdl_rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
