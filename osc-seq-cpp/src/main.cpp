#include <SDL.h>
#include <oscpp/client.hpp>
#include <asio.hpp>
#include <stdio.h>
#include <array>
#include <string>
#include "osc/osc.hpp"
#include "sdl/sdl_wrapper.hpp"
#include "sequencer.hpp"
#include "store/store.hpp"

int main(int argc, char* args[]) {
    send_osc_packet();

    Store* store = new Store();

    loop(store);

    SDL_DestroyWindow(store->window);
    SDL_Quit();
    return 0;
}
