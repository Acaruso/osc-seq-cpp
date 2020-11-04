#pragma once
#include <array>
#include <string>

const size_t MAX_PACKET_SIZE = 8192;

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

size_t make_osc_packet(void* buffer, size_t size);

void send_osc_packet();
