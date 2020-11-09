#include "osc/osc.hpp"
#include "sequencer.hpp"
#include "store/store.hpp"

int main(int argc, char* args[]) {
    Store store;

    loop(store);

    SDL_DestroyWindow(store.window);
    SDL_Quit();
    return 0;
}
