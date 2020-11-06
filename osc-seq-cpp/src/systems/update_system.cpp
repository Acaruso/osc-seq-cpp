#include "update_system.hpp"

void update_system(Store& store) {
    store.clock = (store.clock + 1) % 2048;
}
