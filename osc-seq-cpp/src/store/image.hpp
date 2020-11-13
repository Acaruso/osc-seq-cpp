#pragma once

#include <SDL.h>

struct Image {
    SDL_Texture* texture;
    int w;
    int h;
};

struct Image_Set {
    Image image;
    Image image_hot;
    Image image_active;
    Image image_toggled;
};
