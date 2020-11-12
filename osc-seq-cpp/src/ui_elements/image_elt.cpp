#include "image_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"

void image_elt_clickable(
    Image_Set image_set,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    Rect rect;
    rect.x = coord.x;
    rect.y = coord.y;
    SDL_QueryTexture(image_set.image, NULL, NULL, &rect.w, &rect.h);

    SDL_Texture* display_image = image_set.image;

    if (is_coord_inside_rect(ui_state.x, ui_state.y, rect)) {
        if (ui_state.click) {
            display_image = image_set.image_active;
        } else {
            display_image = image_set.image_hot;
        }
    }

    if (is_mouseup_inside_rect(rect, ui_state)) {
        on_click();
    }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(window_renderer, display_image, NULL, &sdl_rect);
}

void image_elt_clickable_toggleable(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    Ui_State& ui_state,
    SDL_Renderer* window_renderer,
    std::function<void()> on_click
) {
    Rect rect;
    rect.x = coord.x;
    rect.y = coord.y;
    SDL_QueryTexture(image_set.image, NULL, NULL, &rect.w, &rect.h);

    SDL_Texture* display_image = image_set.image;

    if (is_mouseup_inside_rect(rect, ui_state)) {
        on_click();
        display_image = !toggled ? image_set.image_toggled : image_set.image_hot;
    }
    else if (is_clicked(rect, ui_state)) {
        display_image = image_set.image_active;
    }
    else if (toggled) {
        display_image = image_set.image_toggled;
    }
    else if (is_coord_inside_rect(ui_state.x, ui_state.y, rect)) {
        display_image = image_set.image_hot;
    }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(window_renderer, display_image, NULL, &sdl_rect);
}

void image_elt_toggleable(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    SDL_Renderer* window_renderer
) {
    Rect rect;
    rect.x = coord.x;
    rect.y = coord.y;
    SDL_QueryTexture(image_set.image, NULL, NULL, &rect.w, &rect.h);

    SDL_Texture* display_image = image_set.image;

    if (toggled) {
        display_image = image_set.image_toggled;
    }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(window_renderer, display_image, NULL, &sdl_rect);
}
