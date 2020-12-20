#pragma once

#include <array>
#include <string>
#include <vector>

#include "../store/grid/grid.hpp"
#include "../store/grid/grid_cell.hpp"

const size_t MAX_PACKET_SIZE = 512;

void send_osc_packet(Grid_Cell& grid_cell);

size_t make_osc_packet(
    Grid_Cell& grid_cell,
    void* buffer,
    size_t size
);

void send_udp_message(
    const std::array<char, MAX_PACKET_SIZE>& message,
    const std::string& destination_ip,
    const unsigned short port
);
