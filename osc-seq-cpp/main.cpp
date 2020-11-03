#include <SDL.h>
#include <oscpp/client.hpp>
#include <asio.hpp>
#include <stdio.h>
#include <array>
#include <string>
#include "osc.hpp"
#include "sdl_wrapper.hpp"

int main(int argc, char* args[]) {
    send_osc_packet();

    Init_sdl_res* res = init_sdl();

    SDL_FillRect(
        res->window_surface, 
        NULL, 
        SDL_MapRGB(res->window_surface->format, 0xFF, 0xFF, 0xFF)
    );

    SDL_UpdateWindowSurface(res->window);

    SDL_Delay(1000);

    SDL_DestroyWindow(res->window);

    SDL_Quit();

    return 0;
}
