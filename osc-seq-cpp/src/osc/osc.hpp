#pragma once

#include <array>
#include <string>
#include <vector>

#include "../store/grid.hpp"
#include "../store/grid_cell.hpp"

const size_t MAX_PACKET_SIZE = 512;

void send_osc_packet(int channel);

void send_osc_packet(Grid_Cell& grid_cell);

size_t make_osc_packet(int channel, void* buffer, size_t size);

size_t make_osc_packet(
    int channel,
    void* buffer,
    size_t size,
    std::vector<Event_Field>& fields
);

void send_udp_message(
    const std::array<char, MAX_PACKET_SIZE>& message,
    const std::string& destination_ip,
    const unsigned short port
);

void send_udp_message(
    const std::string& message,
    const std::string& destination_ip,
    const unsigned short port
);
