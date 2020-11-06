#include <asio.hpp>
#include <oscpp/client.hpp>
#include <array>
#include <string>
#include "osc.hpp"

void send_udp_message(
    const std::array<char, MAX_PACKET_SIZE>& message,
    const std::string& destination_ip,
    const unsigned short port
) {
    asio::io_service io_service;
    asio::ip::udp::socket socket(io_service);
    auto remote = asio::ip::udp::endpoint(asio::ip::address::from_string(destination_ip), port);
    socket.open(asio::ip::udp::v4());
    socket.send_to(asio::buffer(message), remote);
}

void send_udp_message(
    const std::string& message,
    const std::string& destination_ip,
    const unsigned short port
) {
    asio::io_service io_service;
    asio::ip::udp::socket socket(io_service);
    auto remote = asio::ip::udp::endpoint(asio::ip::address::from_string(destination_ip), port);
    socket.open(asio::ip::udp::v4());
    socket.send_to(asio::buffer(message), remote);
}

size_t make_osc_packet(void* buffer, size_t size) {
    OSCPP::Client::Packet packet(buffer, size);
    packet
        .openMessage("/0", 1)
        .int32(123)
        .closeMessage();

    return packet.size();
}

void send_osc_packet() {
    std::array<char, MAX_PACKET_SIZE> buffer;
    const size_t packetSize = make_osc_packet(buffer.data(), buffer.size());
    send_udp_message(buffer, "127.0.0.1", 3333);
}
