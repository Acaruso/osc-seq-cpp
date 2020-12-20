#pragma once

#include <string>
#include <vector>
#include <variant>

#include <SDL.h>
#include <SDL_FontCache.h>

#include "../store/color.hpp"
#include "../store/coord.hpp"
#include "../store/image.hpp"
#include "../store/store.hpp"
#include "../store/rect.hpp"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

// for z_axis, bigger number == on top of smaller number
struct Draw_Rect_Data
{
    Rect rect;
    Color color;
    int z_axis;
};

struct Draw_Image_Data
{
    SDL_Texture* texture;
    Rect rect;
    int z_axis;
};

struct Draw_Text_Data
{
    std::string text;
    Coord coord;
    FC_Font* font;
    int z_axis;
};

void push_rect(
    Rect rect,
    Color color,
    int z_axis
);

void push_image(
    SDL_Texture* texture,
    Rect rect,
    int z_axis
);

void push_text(
    std::string text,
    Coord coord,
    FC_Font* font,
    int z_axis
);

struct Init_Sdl_Res
{
	SDL_Window* window;
	SDL_Surface* window_surface;
	SDL_Renderer* window_renderer;
};

Init_Sdl_Res init_sdl();

void clear_window(SDL_Renderer* window_renderer);

void draw_rect(Rect& rect, Color& color, SDL_Renderer* window_renderer);

Image load_image(std::string path, SDL_Renderer* window_renderer);

void draw_image(
    SDL_Texture* texture,
    Rect& rect,
    SDL_Renderer* window_renderer
);

SDL_Rect rect_to_sdl_rect(Rect rect);

FC_Rect draw_text(
    std::string text,
    Coord& coord,
    FC_Font* font,
    SDL_Renderer* window_renderer
);
