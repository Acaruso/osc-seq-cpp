#include <asio.hpp>
#include <oscpp/client.hpp>
#include <array>
#include <string>
#include "osc.hpp"

void send_osc_packet(int channel) {
    std::array<char, MAX_PACKET_SIZE> buffer;
    const size_t packetSize = make_osc_packet(channel, buffer.data(), buffer.size());
    send_udp_message(buffer, "127.0.0.1", 3333);
}

size_t make_osc_packet(int channel, void* buffer, size_t size) {
    std::string channel_str = "/" + std::to_string(channel);

    OSCPP::Client::Packet packet(buffer, size);
    packet
        .openMessage(channel_str.c_str(), 1)
        .int32(123)
        .closeMessage();

    return packet.size();
}

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
