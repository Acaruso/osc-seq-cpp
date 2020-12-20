#include "image_elt.hpp"

#include <iostream>

#include "../sdl/sdl_wrapper.hpp"
#include "../store/coord.hpp"
#include "../store/rect.hpp"
#include "../store/store.hpp"
#include "../util.hpp"

void image_elt(
    Image_Set& image_set,
    Coord& coord,
    Store& store
) {
    SDL_Texture* display_image = image_set.image.texture;

    Rect rect{
        coord.x,
        coord.y,
        image_set.image.w,
        image_set.image.h
    };

    draw_image(display_image, rect, store.window_renderer);
}

void image_elt_clickable(
    Image_Set& image_set,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
) {
    Rect rect = { coord.x, coord.y, image_set.image.w, image_set.image.h };

    SDL_Texture* display_image = image_set.image.texture;

    if (is_coord_inside_rect(store.ui_state.cx, store.ui_state.cy, rect)) {
        if (store.ui_state.click) {
            display_image = image_set.image_active.texture;
        } else {
            display_image = image_set.image_hot.texture;
        }
    }

    if (is_mouseup_event_inside_rect(rect, store.ui_state, store.prev_ui_state)) {
        on_click();
    }

    draw_image(display_image, rect, store.window_renderer);
}

void image_elt_clickable_toggleable(
    Image_Set& image_set,
    bool toggled,
    Coord& coord,
    Store& store,
    std::function<void()> on_click
) {
    Rect rect = { coord.x, coord.y, image_set.image.w, image_set.image.h };

    SDL_Texture* display_image = image_set.image.texture;

    if (is_mouseup_event_inside_rect(rect, store.ui_state, store.prev_ui_state)) {
        on_click();
        if (!toggled) {
            display_image = image_set.image_toggled.texture;
        } else {
            image_set.image_hot.texture;
        }
    }
    else if (is_clicked(rect, store.ui_state) && !toggled) {
        display_image = image_set.image_active.texture;
    }
    else if (toggled) {
        display_image = image_set.image_toggled.texture;
    }
    else if (is_coord_inside_rect(store.ui_state.cx, store.ui_state.cy, rect)) {
        display_image = image_set.image_hot.texture;
    }

    draw_image(display_image, rect, store.window_renderer);
}

void image_elt_toggleable(
    Image_Set& image_set,
    bool toggled,
    Coord& coord,
    Store& store
) {
    Rect rect = { coord.x, coord.y, image_set.image.w, image_set.image.h };

    SDL_Texture* display_image = !toggled
        ? image_set.image.texture
        : image_set.image_toggled.texture;

    draw_image(display_image, rect, store.window_renderer);
}

void image_elt_blink(
    Image_Set& image_set,
    Coord& coord,
    Store& store
) {
    if ((store.blink_clock / 32) % 2 == 0) {
        SDL_Texture* display_image = image_set.image.texture;

        Rect rect{
            coord.x,
            coord.y,
            image_set.image.w,
            image_set.image.h
        };

        draw_image(display_image, rect, store.window_renderer);
    }
}
