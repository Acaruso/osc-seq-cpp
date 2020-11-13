#pragma once

#include <SDL.h>

struct Image {
    SDL_Texture* image_texture;
    int w;
    int h;
};

struct Image_Set {
    SDL_Texture* image;
    SDL_Texture* image_hot;
    SDL_Texture* image_active;
    SDL_Texture* image_toggled;
};
