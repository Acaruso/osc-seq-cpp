#include "image_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/rect.hpp"
#include "../util.hpp"

void image_elt(
    Image_Set image_set,
    Coord& coord,
    Store& store
) {
    SDL_Texture* display_image = image_set.image.texture;

    SDL_Rect sdl_rect;
    sdl_rect.x = coord.x;
    sdl_rect.y = coord.y;
    sdl_rect.w = image_set.image.w;
    sdl_rect.h = image_set.image.h;

    SDL_RenderCopy(store.window_renderer, display_image, NULL, &sdl_rect);
}

void image_elt_clickable(
    Image_Set image_set,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
) {
    Rect rect = { coord.x, coord.y, image_set.image.w, image_set.image.h };

    SDL_Texture* display_image = image_set.image.texture;

    if (is_coord_inside_rect(store.ui_state.x, store.ui_state.y, rect)) {
        if (store.ui_state.click) {
            display_image = image_set.image_active.texture;
        } else {
            display_image = image_set.image_hot.texture;
        }
    }

    if (is_mouseup_event_inside_rect(rect, store.ui_state, store.prev_ui_state)) {
        on_click();
    }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(store.window_renderer, display_image, NULL, &sdl_rect);
}

void image_elt_clickable_toggleable(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
) {
    Rect rect = { coord.x, coord.y, image_set.image.w, image_set.image.h };

    SDL_Texture* display_image = image_set.image.texture;

    if (is_mouseup_event_inside_rect(rect, store.ui_state, store.prev_ui_state)) {
        on_click();
        display_image = !toggled
            ? image_set.image_toggled.texture
            : image_set.image_hot.texture;
    }
    else if (is_clicked(rect, store.ui_state) && !toggled) {
        display_image = image_set.image_active.texture;
    }
    else if (toggled) {
        display_image = image_set.image_toggled.texture;
    }
    else if (is_coord_inside_rect(store.ui_state.x, store.ui_state.y, rect)) {
        display_image = image_set.image_hot.texture;
    }

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(store.window_renderer, display_image, NULL, &sdl_rect);
}

void image_elt_toggleable(
    Image_Set image_set,
    bool toggled,
    Coord& coord,
    Store& store
) {
    Rect rect = { coord.x, coord.y, image_set.image.w, image_set.image.h };

    SDL_Texture* display_image = !toggled
        ? image_set.image.texture
        : image_set.image_toggled.texture;

    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);

    SDL_RenderCopy(store.window_renderer, display_image, NULL, &sdl_rect);
}

void image_elt_blink(
    Image_Set image_set,
    Coord& coord,
    Store& store
) {
    if ((store.blink_clock / 32) % 2 == 0) {
        SDL_Texture* display_image = image_set.image.texture;

        SDL_Rect sdl_rect;
        sdl_rect.x = coord.x;
        sdl_rect.y = coord.y;
        sdl_rect.w = image_set.image.w;
        sdl_rect.h = image_set.image.h;

        SDL_RenderCopy(store.window_renderer, display_image, NULL, &sdl_rect);
    }
}
