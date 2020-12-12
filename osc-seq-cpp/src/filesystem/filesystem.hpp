#pragma once

#include "../store/store.hpp"

#include <string>

void save_file(std::string path, Store& store);

void open_file(std::string path, Store& store);
