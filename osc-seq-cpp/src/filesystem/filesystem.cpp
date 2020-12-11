#include "filesystem.hpp"

#include <fstream>

void save_file(std::string path, Store& store)
{
    std::ofstream out(path);
    if (out.is_open()) {
        out << store.bpm << std::endl;
    }
}
