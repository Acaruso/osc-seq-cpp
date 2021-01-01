#include "filesystem.hpp"

#include "serialize.hpp"

#include <fstream>
#include <iostream>

void save_file(std::string path, Store& store)
{
    std::ofstream fs(path);
    if (fs.is_open()) {
        fs << serialize_store(store);
    }
}

void open_file(std::string path, Store& store)
{
    std::string str;
    std::ifstream fs(path);
    if (fs.is_open()) {
        // store.deserialize(fs);
    }
}
