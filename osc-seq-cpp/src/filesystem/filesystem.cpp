#include "filesystem.hpp"

#include <fstream>
#include <iostream>

void save_file(std::string path, Store& store)
{
    std::ofstream fs(path);
    if (fs.is_open()) {
        fs << store.serialize();
    }
}

void open_file(std::string path, Store& store)
{
    std::string str;
    std::ifstream fs(path);
    if (fs.is_open()) {
        store.deserialize(fs);
        // while (std::getline(fs, str)) {
        //     std::cout << str << std::endl;
        // }
    }
}