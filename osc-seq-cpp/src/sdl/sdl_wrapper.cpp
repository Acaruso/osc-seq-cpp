#include "sdl_wrapper.hpp"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <algorithm>
#include <iostream>

std::vector<Draw_Data> draw_queue;

void push_rect(
    Rect rect,
    Color color,
    int z_axis
) {
    draw_queue.push_back(Draw_Rect_Data{rect, color, z_axis});
}

void push_image(
    SDL_Texture* texture,
    Rect rect,
    int z_axis
) {
    draw_queue.push_back(Draw_Image_Data{texture, rect, z_axis});
}

void push_text(
    std::string text,
    Coord coord,
    FC_Font* font,
    int z_axis
) {
    draw_queue.push_back(Draw_Text_Data{text, coord, font, z_axis});
}

void Draw_Rect_Data::draw(SDL_Renderer* renderer)
{
    draw_rect(rect, color, renderer);
}

void Draw_Image_Data::draw(SDL_Renderer* renderer)
{
    draw_image(texture, rect, renderer);
}

void Draw_Text_Data::draw(SDL_Renderer* renderer)
{
    draw_text(text, coord, font, renderer);
}

auto get_z_axis = [](auto& value) { return value.z_axis; };

void draw_from_queue(SDL_Renderer* renderer)
{
    std::sort(
        std::begin(draw_queue),
        std::end(draw_queue),
        [](auto& a, auto& b) {
            return std::visit(get_z_axis, a) > std::visit(get_z_axis, b);
        }
    );

    while (!draw_queue.empty()) {
        auto do_draw = [&](auto& value) { value.draw(renderer); };
        std::visit(do_draw, draw_queue.back());
        draw_queue.pop_back();
    }
}

Init_Sdl_Res init_sdl()
{
	Init_Sdl_Res res;

	SDL_Init(SDL_INIT_EVERYTHING);

    IMG_Init(IMG_INIT_PNG);

    TTF_Init();

	res.window = SDL_CreateWindow(
		"osc-seq",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	res.window_surface = SDL_GetWindowSurface(res.window);
	res.window_renderer = SDL_CreateRenderer(res.window, -1, SDL_RENDERER_ACCELERATED);

	return res;
}

void clear_window(SDL_Renderer* window_renderer)
{
	SDL_SetRenderDrawColor(window_renderer, 255, 255, 255, 255);
	SDL_RenderClear(window_renderer);
}

void draw_rect(Rect& rect, Color& color, SDL_Renderer* window_renderer)
{
    SDL_Rect sdl_rect;
    sdl_rect.w = rect.w;
    sdl_rect.h = rect.h;
    sdl_rect.x = rect.x;
    sdl_rect.y = rect.y;

    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(window_renderer, &sdl_rect);
}

Image load_image(std::string path, SDL_Renderer* window_renderer)
{
    SDL_Surface* buffer = IMG_Load(path.c_str());

    if (!buffer) {
        std::cout << "error loading image " << SDL_GetError() << std::endl;
    }

    Image image;
    image.texture = SDL_CreateTextureFromSurface(window_renderer, buffer);
    image.w = buffer->w;
    image.h = buffer->h;

    if (!image.texture) {
        std::cout << "error creating texture " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(buffer);

    return image;
}

void draw_image(
    SDL_Texture* texture,
    Rect& rect,
    SDL_Renderer* window_renderer
) {
    SDL_Rect sdl_rect = rect_to_sdl_rect(rect);
    SDL_RenderCopy(window_renderer, texture, NULL, &sdl_rect);
}

SDL_Rect rect_to_sdl_rect(Rect rect)
{
    SDL_Rect sdl_rect;
    sdl_rect.x = rect.x;
    sdl_rect.y = rect.y;
    sdl_rect.w = rect.w;
    sdl_rect.h = rect.h;
    return sdl_rect;
}

FC_Rect draw_text(
    std::string text,
    Coord& coord,
    FC_Font* font,
    SDL_Renderer* window_renderer
) {
    return FC_Draw(font, window_renderer, coord.x, coord.y, text.c_str());
}
